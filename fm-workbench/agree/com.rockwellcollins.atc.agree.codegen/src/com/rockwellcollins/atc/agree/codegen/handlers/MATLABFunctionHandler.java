package com.rockwellcollins.atc.agree.codegen.handlers;

import java.io.PrintWriter;
import java.io.StringWriter;
import jkind.lustre.Node;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Status;
import org.eclipse.emf.common.util.EList;
import org.osate.aadl2.AnnexSubclause;
import org.osate.aadl2.ComponentImplementation;
import org.osate.aadl2.ComponentType;
import org.osate.aadl2.Element;
import org.osate.aadl2.instance.SystemInstance;
import org.osate.aadl2.instantiation.InstantiateModel;
import org.osate.annexsupport.AnnexUtil;
import org.osate.ui.dialogs.Dialog;

import com.rockwellcollins.atc.agree.agree.AgreePackage;
import com.rockwellcollins.atc.agree.analysis.AgreeException;
import com.rockwellcollins.atc.agree.analysis.AgreeUtils;
import com.rockwellcollins.atc.agree.analysis.ast.AgreeASTBuilder;
import com.rockwellcollins.atc.agree.analysis.ast.AgreeProgram;
import com.rockwellcollins.atc.agree.analysis.handlers.AadlHandler;
import com.rockwellcollins.atc.agree.analysis.translation.AgreeNodeToLustreContract;
import com.rockwellcollins.atc.agree.codegen.Activator;
import com.rockwellcollins.atc.agree.codegen.ast.MATLABPrimaryFunction;
import com.rockwellcollins.atc.agree.codegen.translation.LustreToMATLABTranslator;

/**
 * Our sample handler extends AbstractHandler, an IHandler base class.
 * @see org.eclipse.core.commands.IHandler
 * @see org.eclipse.core.commands.AbstractHandler
 */
public class MATLABFunctionHandler extends AadlHandler {
	/**
	 * The constructor.
	 */
	public MATLABFunctionHandler() {
	}

    protected String getNestedMessages(Throwable e) {
        StringWriter sw = new StringWriter();
        PrintWriter pw = new PrintWriter(sw);
        while (e != null) {
            if (e.getMessage() != null && !e.getMessage().isEmpty()) {
                pw.println(e.getMessage());
            }
            e = e.getCause();
        }
        pw.close();
        return sw.toString();
    }
	
    protected IStatus runJob(Element root, IProgressMonitor monitor) {
        if (!(root instanceof ComponentImplementation)) {
            return new Status(IStatus.ERROR, Activator.PLUGIN_ID,
                    "Must select an AADL Component Implementation");
        }

        try {
            ComponentImplementation ci = (ComponentImplementation) root;

            SystemInstance si = null;
            try {
                si = InstantiateModel.buildInstanceModelFile(ci);
            } catch (Exception e) {
                Dialog.showError("Model Instantiate",
                        "Error while re-instantiating the model: " + e.getMessage());
                return Status.CANCEL_STATUS;
            }

            // SystemType sysType = si.getSystemImplementation().getType();
            ComponentType sysType = AgreeUtils.getInstanceType(si);
            EList<AnnexSubclause> annexSubClauses = AnnexUtil.getAllAnnexSubclauses(sysType,
                    AgreePackage.eINSTANCE.getAgreeContractSubclause());

            if (annexSubClauses.size() == 0) {
                throw new AgreeException(
                        "There is not an AGREE annex in the '" + sysType.getName() + "' system type.");
            }
            
            //Get Agree program
            AgreeProgram agreeProgram = new AgreeASTBuilder().getAgreeProgram(si);

            //Translate Agree Node to Lustre Node with pre-statement flatten, helper nodes inlined,
            //and variable declarations sorted so they are declared before use
            Node lustreNode = AgreeNodeToLustreContract.translate(agreeProgram.topNode, agreeProgram);
            
            //Translate Lustre Node to MATLAB Function AST
            MATLABPrimaryFunction matlabFunction = LustreToMATLABTranslator.translate(lustreNode);
            
            //Walk through MATLAB function AST and print out
            System.out.println(matlabFunction);
            //TODO write to MATLAB script file with the same name as the primary function
            return Status.OK_STATUS;
        } catch (Throwable e) {
            String messages = getNestedMessages(e);
            return new Status(IStatus.ERROR, Activator.PLUGIN_ID, 0, messages, e);
        }
    }
	
	protected String getJobName() {
		 return "AGREE - Generate Matlab Function Single Layer";
	}
	
}
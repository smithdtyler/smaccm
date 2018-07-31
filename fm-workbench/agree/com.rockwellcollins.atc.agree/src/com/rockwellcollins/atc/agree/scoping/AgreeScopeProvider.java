/*
 * generated by Xtext
 */
package com.rockwellcollins.atc.agree.scoping;

import java.util.HashSet;
import java.util.Set;
import java.util.Stack;

import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EReference;
import org.eclipse.xtext.scoping.IScope;
import org.eclipse.xtext.scoping.Scopes;
import org.eclipse.xtext.scoping.impl.FilteringScope;
import org.osate.aadl2.Aadl2Package;
import org.osate.aadl2.AadlPackage;
import org.osate.aadl2.AnnexLibrary;
import org.osate.aadl2.AnnexSubclause;
import org.osate.aadl2.Classifier;
import org.osate.aadl2.ComponentClassifier;
import org.osate.aadl2.ComponentImplementation;
import org.osate.aadl2.ComponentType;
import org.osate.aadl2.DataImplementation;
import org.osate.aadl2.DataPort;
import org.osate.aadl2.DataType;
import org.osate.aadl2.Element;
import org.osate.aadl2.EventDataPort;
import org.osate.aadl2.NamedElement;
import org.osate.aadl2.PublicPackageSection;
import org.osate.aadl2.Subcomponent;
import org.osate.aadl2.ThreadSubcomponent;
import org.osate.aadl2.impl.FeatureGroupImpl;
import org.osate.annexsupport.AnnexUtil;

import com.rockwellcollins.atc.agree.agree.AgreeContract;
import com.rockwellcollins.atc.agree.agree.AgreeContractLibrary;
import com.rockwellcollins.atc.agree.agree.AgreeContractSubclause;
import com.rockwellcollins.atc.agree.agree.AgreeLibrary;
import com.rockwellcollins.atc.agree.agree.AgreePackage;
import com.rockwellcollins.atc.agree.agree.Arg;
import com.rockwellcollins.atc.agree.agree.ConnectionStatement;
import com.rockwellcollins.atc.agree.agree.ConstStatement;
import com.rockwellcollins.atc.agree.agree.EnumStatement;
import com.rockwellcollins.atc.agree.agree.EqStatement;
import com.rockwellcollins.atc.agree.agree.FnDefExpr;
import com.rockwellcollins.atc.agree.agree.InputStatement;
import com.rockwellcollins.atc.agree.agree.LibraryFnDefExpr;
import com.rockwellcollins.atc.agree.agree.LinearizationDefExpr;
import com.rockwellcollins.atc.agree.agree.NestedDotID;
import com.rockwellcollins.atc.agree.agree.NodeDefExpr;
import com.rockwellcollins.atc.agree.agree.OrderStatement;
import com.rockwellcollins.atc.agree.agree.RecordDefExpr;
import com.rockwellcollins.atc.agree.agree.RecordExpr;
import com.rockwellcollins.atc.agree.agree.RecordType;
import com.rockwellcollins.atc.agree.agree.RecordUpdateExpr;
import com.rockwellcollins.atc.agree.agree.SpecStatement;
import com.rockwellcollins.atc.agree.agree.SynchStatement;
import com.rockwellcollins.atc.agree.agree.Type;

/**
 * This class contains custom scoping description.
 *
 * see : http://www.eclipse.org/Xtext/documentation.html#scoping on how and when
 * to use it
 *
 */
public class AgreeScopeProvider extends org.osate.xtext.aadl2.properties.scoping.PropertiesScopeProvider {

	IScope scope_NamedElement(FnDefExpr ctx, EReference ref) {
		return Scopes.scopeFor(ctx.getArgs(), getScope(ctx.eContainer(), ref));
	}

	IScope scope_NamedElement(LinearizationDefExpr ctx, EReference ref) {
		return Scopes.scopeFor(ctx.getArgs(), getScope(ctx.eContainer(), ref));
	}

	IScope scope_NamedElement(LibraryFnDefExpr ctx, EReference ref) {
		return Scopes.scopeFor(ctx.getArgs(), getScope(ctx.eContainer(), ref));
	}

	IScope scope_RecordExpr_args(RecordExpr ctx, EReference ref) {
		NestedDotID record = ctx.getRecord();
		while (record.getSub() != null) {
			record = record.getSub();
		}
		NamedElement recDef = record.getBase();
		return RecordExprScoper.getRecordComponents(recDef, IScope.NULLSCOPE);
	}

	private Stack<EObject> contextStack = new Stack<>();

	IScope scope_RecordUpdateExpr_args(RecordUpdateExpr ctx, EReference ref) {
		// This strange-looking construct is to handle the RecordUpdateExpr
		// construct where the record to be updated is itself an Expr and we
		// must use the RecordExprScoper to look inward at that expression to
		// determine the scope but still handle that it looks back outward
		// at the containing scopes. This check determines whether we are
		// already handling the RecordUpdateExpr and merely passes back to
		// the containing scope if we are. Thus, we avoid a cyclic linking
		// error.
		if (contextStack.contains(ctx)) {
			return getScope(ctx.eContainer(), ref);
		} else {
			try {
				contextStack.push(ctx);
				return RecordExprScoper.getScope(ctx.getRecord(), IScope.NULLSCOPE);
			} finally {
				contextStack.pop();
			}
		}
	}

	IScope scope_NamedElement(NodeDefExpr ctx, EReference ref) {
		Set<Element> components = new HashSet<>();
		components.addAll(ctx.getArgs());
		components.addAll(ctx.getRets());
		components.addAll(ctx.getNodeBody().getLocs());
		IScope outer = new FilteringScope(getScope(ctx.eContainer(), ref),
				input -> (AgreePackage.eINSTANCE.getNodeDefExpr().isSuperTypeOf(input.getEClass())
						|| AgreePackage.eINSTANCE.getRecordDefExpr().isSuperTypeOf(input.getEClass())
						|| AgreePackage.eINSTANCE.getConstStatement().isSuperTypeOf(input.getEClass())
						|| Aadl2Package.eINSTANCE.getAadlPackage().isSuperTypeOf(input.getEClass())
						|| Aadl2Package.eINSTANCE.getComponentClassifier().isSuperTypeOf(input.getEClass())));
		return Scopes.scopeFor(components, outer);
	}

	protected IScope scope_NamedElement(AgreeContract ctx, EReference ref) {
		Set<Element> components = new HashSet<>();
		components.addAll(getAllElementsFromSpecs(ctx.getSpecs()));
		return Scopes.scopeFor(components, getAadlScope(ctx.eContainer(), ref));
	}

	IScope scope_NamedElement(ConnectionStatement ctx, EReference ref) {
		EObject container = ctx.getContainingClassifier();
		IScope outerScope = IScope.NULLSCOPE;
		if (container instanceof ComponentImplementation) {
			ComponentImplementation compImpl = (ComponentImplementation) container;
			outerScope = Scopes.scopeFor(compImpl.getAllConnections());
		}
		return outerScope;
	}

	IScope scope_NamedElement(OrderStatement ctx, EReference ref) {
		EObject container = ctx.getContainingClassifier();

		IScope outerScope = IScope.NULLSCOPE;
		if (container instanceof ComponentImplementation) {
			ComponentImplementation compImpl = (ComponentImplementation) container;
			outerScope = Scopes.scopeFor(compImpl.getAllSubcomponents());
		}
		return outerScope;
	}

	IScope scope_NamedElement(SynchStatement ctx, EReference ref) {
		EObject container = ctx.getContainingClassifier();
		while (!(container instanceof ComponentClassifier)) {
			container = container.eContainer();
		}

		if (container instanceof ComponentImplementation) {
			return Scopes.scopeFor(((ComponentImplementation) container).getAllSubcomponents());
		}
		return IScope.NULLSCOPE;
	}

	protected IScope scope_NamedElement(NestedDotID ctx, EReference ref) {
		return Scopes.scopeFor(getCorrespondingAadlElement(ctx, ref), getScope(ctx.eContainer(), ref));
	}

	private Set<Element> getCorrespondingAadlElement(NestedDotID id, EReference ref) {
		EObject container = id.eContainer();
		Set<Element> result = new HashSet<>();

		if (container instanceof NestedDotID) {
			NestedDotID parent = (NestedDotID) container;
			EList<EObject> refs = parent.eCrossReferences();

			if (refs.size() != 1) {
				return new HashSet<>(); // this will throw a parsing error
			}
			container = refs.get(0); // figure out what this type this portion
			// of the nest id is so we can figure out
			// what we could possibly link to

			if (container instanceof ThreadSubcomponent) {
				container = ((ThreadSubcomponent) container).getComponentType();
			} else if (container instanceof Subcomponent) {
				container = ((Subcomponent) container).getComponentImplementation();
				if (container == null) { // no implementation is provided
					container = refs.get(0);
					container = ((Subcomponent) container).getClassifier();
				}
				result.addAll(getAadlElements(container));
			} else if (container instanceof DataPort) {
				container = ((DataPort) container).getDataFeatureClassifier();
				result.addAll(getAadlElements(container));
			} else if (container instanceof EventDataPort) {
				container = ((EventDataPort) container).getDataFeatureClassifier();
				result.addAll(getAadlElements(container));
			} else if (container instanceof AadlPackage) {
				result.addAll(getAadlElements(container));
			} else if (container instanceof FeatureGroupImpl) {
				container = ((FeatureGroupImpl) container).getAllFeatureGroupType();
				result.addAll(getAadlElements(container));
			} else if (container instanceof Arg || container instanceof ConstStatement) {
				Type type;

				if (container instanceof Arg) {
					type = ((Arg) container).getType();
				} else {
					type = ((ConstStatement) container).getType();
				}

				if (type instanceof RecordType) {
					NestedDotID elID = ((RecordType) type).getRecord();
					while (elID.getSub() != null) {
						elID = elID.getSub();
					}
					NamedElement namedEl = elID.getBase();

					if (namedEl instanceof ComponentImplementation) {
						ComponentImplementation componentImplementation = (ComponentImplementation) namedEl;
						EList<Subcomponent> subs = componentImplementation.getAllSubcomponents();
						result.addAll(subs);
					} else if (namedEl instanceof RecordDefExpr) {
						result.addAll(((RecordDefExpr) namedEl).getArgs());
					}
					return result;
				}

			} else {
				return result; // this will throw a parsing error
			}
		}

		return result;
	}

	private Set<Element> getAllAgreeElements(EObject eobj) {
		Set<Element> result = new HashSet<>();
		if (eobj instanceof Classifier) {
			for (AnnexSubclause subclause : AnnexUtil.getAllAnnexSubclauses((Classifier) eobj,
					AgreePackage.eINSTANCE.getAgreeContractSubclause())) {
				if (subclause instanceof AgreeContractSubclause) {
					AgreeContractSubclause agreeSubclause = (AgreeContractSubclause) subclause;
					AgreeContract contract = (AgreeContract) agreeSubclause.getContract();
					result.addAll(getAllElementsFromSpecs(contract.getSpecs()));
				}
			}
		}
		return result;
	}

	private Set<Element> getAllElementsFromSpecs(EList<SpecStatement> specs) {
		Set<Element> result = new HashSet<>();
		for (SpecStatement spec : specs) {
			if (spec instanceof EqStatement) {
				EqStatement eq = (EqStatement) spec;
				result.addAll(eq.getLhs());
			} else if (spec instanceof InputStatement) {
				result.addAll(((InputStatement) spec).getLhs());
			} else if (spec instanceof EnumStatement) {
				result.addAll(((EnumStatement) spec).getEnums());
				result.add(spec);
			} else {
				result.add(spec);
			}
		}
		return result;
	}

	protected Set<Element> getAadlElements(EObject ctx) {
		Set<Element> components = new HashSet<>();
		if (ctx instanceof ComponentType) {
			components.addAll(getAllAgreeElements(ctx));
			components.addAll(((ComponentType) ctx).getAllFeatures());

		} else if (ctx instanceof ComponentImplementation) {
			components.addAll(((ComponentImplementation) ctx).getAllSubcomponents());
			components.addAll(((ComponentImplementation) ctx).getAllConnections());
			components.addAll(getAllAgreeElements(ctx));
			components.addAll(getAadlElements(((ComponentImplementation) ctx).getType()));

		} else if (ctx instanceof Classifier) {
			components.addAll(((Classifier) ctx).getAllFeatures());

		} else if (ctx instanceof AadlPackage) {
			PublicPackageSection pubSec = ((AadlPackage) ctx).getPublicSection();
			for (Element el : pubSec.getOwnedElements()) {
				if (el instanceof DataImplementation || el instanceof DataType) {
					components.add(el);
				}
			}
			for (AnnexLibrary annex : AnnexUtil.getAllActualAnnexLibraries(((AadlPackage) ctx),
					AgreePackage.eINSTANCE.getAgreeContractLibrary())) {
				if (annex instanceof AgreeLibrary) {
					AgreeContract contract = (AgreeContract) ((AgreeContractLibrary) annex).getContract();
					components.addAll(getAllElementsFromSpecs(contract.getSpecs()));
				}
			}
			components.add((AadlPackage) ctx);

		}
		return components;
	}

	protected IScope getAadlScope(EObject eobj, EReference ref) {
		if (eobj != null) {
			Set<Element> components = getAadlElements(eobj);
			components.addAll(getAllAgreeElements(eobj));
			if (eobj instanceof AadlPackage) {
				return Scopes.scopeFor(components, getScope(eobj, ref));
			} else {
				return Scopes.scopeFor(components, getAadlScope(eobj.eContainer(), ref));
			}
		}
		return IScope.NULLSCOPE;
	}

}

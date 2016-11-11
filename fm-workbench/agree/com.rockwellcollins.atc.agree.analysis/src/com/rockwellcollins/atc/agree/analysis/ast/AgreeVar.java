package com.rockwellcollins.atc.agree.analysis.ast;

import org.eclipse.emf.ecore.EObject;
import org.osate.aadl2.instance.ComponentInstance;
import com.rockwellcollins.atc.agree.analysis.ast.visitors.AgreeASTVisitor;

import jkind.lustre.Type;
import jkind.lustre.VarDecl;

public class AgreeVar extends VarDecl implements AgreeASTElement {

	public final EObject reference;
	public final ComponentInstance compInst;

	public AgreeVar(String name, Type type, EObject reference, ComponentInstance compInst) {
		super(name, type);
		this.reference = reference;
		this.compInst = compInst;
	}
	
	public AgreeVar(String name, Type type, EObject reference) {
		this(name, type, reference, null);
	}

	@Override
	public int hashCode() {
		return id.hashCode();
	}

	@Override
	public boolean equals(Object obj) {
		if (obj instanceof String) {
			return this.id.equals((String) obj);
		}

		if (!(obj instanceof AgreeVar)) {
			return false;
		}
		return ((AgreeVar) obj).id.equals(id);
	}

	@Override
	public <T> T accept(AgreeASTVisitor<T> visitor) {
		return visitor.visit(this);
	}

}

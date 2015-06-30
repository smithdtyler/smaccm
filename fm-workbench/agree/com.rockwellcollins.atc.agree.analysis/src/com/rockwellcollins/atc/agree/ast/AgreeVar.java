package com.rockwellcollins.atc.agree.ast;

import org.eclipse.emf.ecore.EObject;
import org.osate.aadl2.instance.ComponentInstance;

import jkind.lustre.Type;
import jkind.lustre.VarDecl;

public class AgreeVar extends VarDecl{

	public final EObject reference;
	public final ComponentInstance compInst;
	public AgreeVar(String name, Type type, EObject reference, ComponentInstance compInst){
		super(name, type);
		this.reference = reference;
		this.compInst = compInst;
	}
	
	@Override
	public int hashCode(){
		return id.hashCode();
	}
	
	@Override
	public boolean equals(Object obj){
		if(!(obj instanceof AgreeVar)){
			return false;
		}
		return ((AgreeVar)obj).id.equals(id);
	}
}
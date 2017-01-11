/**
 */
package edu.uah.rsesc.aadlsimulator.xtext.inputConstraint;

import org.eclipse.emf.ecore.EFactory;

/**
 * <!-- begin-user-doc -->
 * The <b>Factory</b> for the model.
 * It provides a create method for each non-abstract class of the model.
 * <!-- end-user-doc -->
 * @see edu.uah.rsesc.aadlsimulator.xtext.inputConstraint.InputConstraintPackage
 * @generated
 */
public interface InputConstraintFactory extends EFactory
{
  /**
   * The singleton instance of the factory.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated
   */
  InputConstraintFactory eINSTANCE = edu.uah.rsesc.aadlsimulator.xtext.inputConstraint.impl.InputConstraintFactoryImpl.init();

  /**
   * Returns a new object of class '<em>Input Constraint</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Input Constraint</em>'.
   * @generated
   */
  InputConstraint createInputConstraint();

  /**
   * Returns a new object of class '<em>Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Expression</em>'.
   * @generated
   */
  Expression createExpression();

  /**
   * Returns a new object of class '<em>Scalar Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Scalar Expression</em>'.
   * @generated
   */
  ScalarExpression createScalarExpression();

  /**
   * Returns a new object of class '<em>Random Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Random Expression</em>'.
   * @generated
   */
  RandomExpression createRandomExpression();

  /**
   * Returns a new object of class '<em>Ref Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Ref Expression</em>'.
   * @generated
   */
  RefExpression createRefExpression();

  /**
   * Returns a new object of class '<em>Interval Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Interval Expression</em>'.
   * @generated
   */
  IntervalExpression createIntervalExpression();

  /**
   * Returns a new object of class '<em>Set Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Set Expression</em>'.
   * @generated
   */
  SetExpression createSetExpression();

  /**
   * Returns a new object of class '<em>Integer Literal</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Integer Literal</em>'.
   * @generated
   */
  IntegerLiteral createIntegerLiteral();

  /**
   * Returns a new object of class '<em>Real Literal</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Real Literal</em>'.
   * @generated
   */
  RealLiteral createRealLiteral();

  /**
   * Returns a new object of class '<em>Boolean Literal</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Boolean Literal</em>'.
   * @generated
   */
  BooleanLiteral createBooleanLiteral();

  /**
   * Returns a new object of class '<em>Binary Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Binary Expression</em>'.
   * @generated
   */
  BinaryExpression createBinaryExpression();

  /**
   * Returns a new object of class '<em>Pre Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Pre Expression</em>'.
   * @generated
   */
  PreExpression createPreExpression();

  /**
   * Returns a new object of class '<em>Random Integer Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Random Integer Expression</em>'.
   * @generated
   */
  RandomIntegerExpression createRandomIntegerExpression();

  /**
   * Returns a new object of class '<em>Random Real Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Random Real Expression</em>'.
   * @generated
   */
  RandomRealExpression createRandomRealExpression();

  /**
   * Returns a new object of class '<em>Random Element Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Random Element Expression</em>'.
   * @generated
   */
  RandomElementExpression createRandomElementExpression();

  /**
   * Returns a new object of class '<em>Element Ref Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Element Ref Expression</em>'.
   * @generated
   */
  ElementRefExpression createElementRefExpression();

  /**
   * Returns a new object of class '<em>Const Ref Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Const Ref Expression</em>'.
   * @generated
   */
  ConstRefExpression createConstRefExpression();

  /**
   * Returns a new object of class '<em>Negative Expression</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return a new object of class '<em>Negative Expression</em>'.
   * @generated
   */
  NegativeExpression createNegativeExpression();

  /**
   * Returns the package supported by this factory.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @return the package supported by this factory.
   * @generated
   */
  InputConstraintPackage getInputConstraintPackage();

} //InputConstraintFactory
package testPackage;

public class Test02 {

	private int instanceNumber;	// instance variable
	private double data; 		// instance variable

	public static String color="white";// class variable
	private static int count=0;			// class variable

	/* constructor overloading */
	public Test02(){	// Explicit constructor
		instanceNumber=count;
		System.out.println("Constructor Called");
		count++;
		data=0.0;
	}
	public Test02(double num){
		this();
		data=num;
	}
	public Test02(Test02 copy){
		this();
		this.data=copy.data;
	}

	public void function() {
		System.out.println("function called: "+instanceNumber);
	}

}

/*
 * 1. member variable = instance variable + class variable
 * 2. 생성자 정의 안해주면, instance 생성시 default constructor 호출
 		정의 해주었으면, Explicit Constructor 호출
 *
 */

package testPackage;

public class Test01 {

	public static void main(String[] args) {
		double db=17.2;		// local variable
		Test02 obj;		// obj: reference variable
		obj= new Test02(db);	// object 생성

		obj.function();
	}

}

/*
 *	1. local variable
 *  2. reference variable, Object
 *
 */

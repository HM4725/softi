package java01;
import java.util.Scanner;

public class Test01 {

	public static void main(String[] args) {
		Scanner keyboard=new Scanner(System.in);
		String str=keyboard.nextLine();
		String binary=Code.StoB(str);
		System.out.println(binary);
		
		System.out.println(Decode.BtoS(binary));
		keyboard.close();
	}

}

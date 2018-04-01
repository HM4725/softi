package java01;

public class Code {

	public static String StoB(String str) {
		int temp;
		String Binary="";
		for(int i=0; i<str.length(); i++) {
			temp=(int)str.charAt(i);
			Binary+=evenParity(DtoB(temp));
		}
		return Binary;
	}
	
	private static String DtoB(int num) {

		if(num<1)	return "0";
		else {
			int remainder;
			Integer iobject;
			String binary="";
			
			while(num!=1) {
				remainder=num%2;
				num/=2;
				iobject=new Integer(remainder);
				binary+= iobject.toString();
			}
			binary+="1";
			
			StringBuffer strbuffer=new StringBuffer();
			strbuffer.append(binary);
			strbuffer.reverse();
			
			binary=strbuffer.toString();
			
			while(binary.length()!=7) {
				binary="0"+binary;
			}
			
			return binary;
		}
	}
	
	private static String evenParity (String str) {
		if (str==null) return "";
		int count=0;
		String ascii="";
		for(int i=0;i<str.length();i++) {
			if(str.charAt(i)=='1') count++;
		}
		
		if (count%2==0)	ascii +="0";
		else	ascii+="1";
		ascii+=str;
		
		return ascii;
	}
}

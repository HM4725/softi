package java01;

public class Decode {
	
	public static String BtoS (String str) {
		String decode="";
		int numofchar= str.length() /8;
		int dec;
		Character temp;
		String ch;

		
		for(int i=0; i<numofchar; i++) {
			ch=str.substring(i*8, (i+1)*8);
			dec=BtoD(ch);
			
			if(dec==-1) {
				return "error";
			}
			
			temp=new Character((char)dec);
			decode+=temp.toString();
		}
		
		return decode;
	}
	
	private static int BtoD (String binary) {
		if (check(binary)) {
			int decimal=0;
			int place=6;
			int factor;
			String rBinary=binary.substring(1,8);
			while(place>=0) {
				if(rBinary.charAt(6-place)=='1') {
					factor=(int) Math.pow(2, place);
					decimal+=factor;
				}
				place--;
			}
			return decimal;			
		}
		else {
			return -1; // error
		}
	}
	
	private static boolean check(String binary) {
		if(binary.length()!=8) return false;
		else {
			int count=0;
			for(int i=0;i<8;i++) {
				if(binary.charAt(i)=='1') count++;
			}
			return (count%2==0);	// even parity
		}
	}
}

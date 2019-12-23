package ftpServer;

import java.net.*;
import java.io.*;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FTPServerProcess {
	
	private DataInputStream inFromClient;
	private DataOutputStream outToClient;

	private InetAddress clientIp;
	private int port;

	private Path path;
	
	private String command;
	private String operator;
	private String argument;
	
	public FTPServerProcess(Socket clientSocket) throws IOException {
		inFromClient = new DataInputStream(clientSocket.getInputStream());
		outToClient = new DataOutputStream(clientSocket.getOutputStream());
		clientIp = clientSocket.getInetAddress();
		port = clientSocket.getPort();
		
		path = Paths.get("");
		path = path.toAbsolutePath();
	}
	
	public void run() throws IOException {
		while(true) {
			
			// receive
			command = inFromClient.readLine();
			parse();
			
			// processing
			if(operator.equals("CD")) {
				cd();
			} else if(operator.equals("LIST")) {
				list();
			} else if(operator.equals("GET")) {
				get();
			} else if(operator.equals("PUT")) {
				put();
			} else if(operator.equals("QUIT")) {
				System.out.println("disconnect");
				break;
			} else {
				Exception e = new Exception();
				e.printStackTrace();
				System.out.println("ERROR: Wrong message");
				break;
			}
			
		}
	}
	
	private void cd() throws IOException {
		File dir;
		boolean isDir;
		Path tempPath;
		String tempPathStr;
		String temp;
		int statusCode;
		int responseLength;
		byte[] header;
		byte[] message;
		byte[] response;
		
		// receive
		tempPath = Paths.get(argument);
		if(!tempPath.isAbsolute()) {
			tempPathStr = path.toString() + "\\" + argument;
		} else {
			tempPathStr = argument;
		}
		
		dir = new File(tempPathStr);
		
		if(dir.isDirectory()) {
			isDir = true;
			statusCode = 1;
		} else {
			isDir = false;
			statusCode = -1;
		}
		
		// send
		if(isDir) {
			tempPathStr = dir.getCanonicalPath();
			response = tempPathStr.getBytes("UTF-8");
			responseLength = response.length;
			temp = statusCode + "\n"
					+ responseLength + "\n";
			header = temp.getBytes("UTF-8");
			message = concatByteArrays(header, response);
			outToClient.write(message);
			path = Paths.get(tempPathStr);
		} else {
			temp = statusCode + "\n"
					+ "Failed - directory name is invalid\n";
			message = temp.getBytes("UTF-8");
			outToClient.write(message);
		}
	}
	
	private void list() throws IOException {
		File dir;
		File[] filesList;
		boolean isDir;
		Path tempPath;
		String temp;
		String tempPathStr;
		int statusCode;
		int responseLength;
		byte[] header;
		byte[] message;
		byte[] response;
		
		// receive
		tempPath = Paths.get(argument);
		if(!tempPath.isAbsolute()) {
			tempPathStr = path.toString() + "\\" + argument;
		} else {
			tempPathStr = argument;
		}
		
		dir = new File(tempPathStr);
		
		if(dir.isDirectory()) {
			isDir = true;
			statusCode = 1;
		} else {
			isDir = false;
			statusCode = -2;	
		}
		
		// send
		if(isDir) {
			temp = "";
			filesList = dir.listFiles();
			for(File f: filesList) {
				if(f.isDirectory()) {
					temp += f.getName() + ",-,";
				} else {
					temp += f.getName() + "," + f.length() + ",";
				}
			}
			if(temp.length() != 0) {
				temp = temp.substring(0, temp.length() - 1);
			}
			response = temp.getBytes("UTF-8");
			responseLength = response.length;
			temp = statusCode + "\n"
					+ responseLength + "\n";
			header = temp.getBytes("UTF-8");
			message = concatByteArrays(header, response);
			outToClient.write(message);
			
		} else {
			temp = statusCode + "\n"
					+ "Failed - directory name is invalid\n";
			message = temp.getBytes("UTF-8");
			outToClient.write(message);
		}
		
	}
	
	private void get() throws IOException {
		File file;
		FileInputStream fin;
		Path tempPath;
		String temp;
		String tempPathStr;
		int statusCode;
		int fileSize;
		byte[] header;
		byte[] message;
		byte[] fileData;
		
		// receive
		tempPath = Paths.get(argument);
		if(!tempPath.isAbsolute()) {
			tempPathStr = path.toString() + "\\" + argument;
		} else {
			tempPathStr = argument;
		}
		
		file = new File(tempPathStr);

		if(file.exists()) {
			if(!file.isDirectory()) {
				statusCode = 1;
			} else {
				statusCode = -3;
			}
		} else {
			statusCode = -4;
		}
		
		// send
		if(statusCode == 1) {
			fin = new FileInputStream(file);
			fileSize = (int)file.length();
			fileData = new byte[fileSize];
			fin.read(fileData, 0, fileSize);
			fin.close();
			
			temp = statusCode + "\n"
					+ fileSize + "\n";
			header = temp.getBytes();
			message = concatByteArrays(header, fileData);
			outToClient.write(message);
			
		} else if(statusCode == -3) {
			temp = statusCode + "\n"
					+ "Failed - The file is a directory.\n";
			message = temp.getBytes("UTF-8");
			outToClient.write(message);
		} else /*statusCode == -4*/ { 
			temp = statusCode + "\n"
					+ "Failed - Such file does not exist!\n";
			message = temp.getBytes("UTF-8");
			outToClient.write(message);
			
		}
		
	}
	
	private void put() {

		File file;
		FileOutputStream fout;
		Path tempPath;
		String temp;
		String tempPathStr;
		int idx;
		int statusCode;
		int fileSize;
		byte[] message;
		byte[] fileData;
		
		try {
			// receive
			temp = inFromClient.readLine();
			fileSize = Integer.parseInt(temp);
			fileData = new byte[fileSize];
			inFromClient.read(fileData, 0, fileSize);
		
			idx = argument.lastIndexOf('.');
			argument = argument.substring(0, idx) 
					+ "_" + clientIp.getHostAddress() 
					+ "_" + port 
					+ argument.substring(idx);
			
			tempPath = Paths.get(argument);
			if(!tempPath.isAbsolute()) {
				tempPathStr = path.toString() + "\\" + argument;
			} else {
				tempPathStr = argument;
			}
		
			file = new File(tempPathStr);

			if(!file.exists()) {
				statusCode = 1;
				fout = new FileOutputStream(file);
				fout.write(fileData, 0, fileSize);
			} else {
				statusCode = -5;
			}
		
			// send
			if(statusCode == 1) {

				temp = statusCode + "\n"
						+ argument + " transferred\n";
				message = temp.getBytes("UTF-8");
				outToClient.write(message);
			
			} else /*statusCode == -5*/ { 
				temp = statusCode + "\n"
						+ "Failed - the file exists that has the same name!\n";
				message = temp.getBytes("UTF-8");
				outToClient.write(message);
			
			}
		} catch(IOException e) {
			statusCode = -10;
			temp = statusCode + "\n"
					+ "Failed for unknown reason.\n";
			try {
				message = temp.getBytes("UTF-8");
				outToClient.write(message);
			} catch (IOException ex) { }
			e.printStackTrace();
		}
		
	}

	private void parse() {
		int idx;
		
		idx = command.indexOf(' ');
		operator = command.substring(0, idx);
		argument = command.substring(idx+1);
	}
	
	
	private byte[] concatByteArrays(byte[] ba1, byte[] ba2) {
		
		byte[] concatArray = new byte[ba1.length + ba2.length];
		for(int i = 0; i < ba1.length + ba2.length ; i++) {
			if(i < ba1.length) {
				concatArray[i] = ba1[i];
			} else {
				concatArray[i] = ba2[i - ba1.length];
			}
		}
		return concatArray;
	}
	

}

package ftpClient;

import java.io.*;
import java.net.*;

public class FTPClientProcess {
	
	private BufferedReader inFromUser;
	private DataOutputStream outToServer;
	private DataInputStream inFromServer;
	
	private String command;
	private String operator;
	private String argument;

	public FTPClientProcess(Socket connectionSocket) throws IOException {
		inFromUser = new BufferedReader(new InputStreamReader(System.in));
		outToServer = new DataOutputStream(connectionSocket.getOutputStream());
		inFromServer = new DataInputStream(connectionSocket.getInputStream());
	}
	
	public void run() throws IOException {

		
		while(true) {
			
			command = inFromUser.readLine();
			if(command.equals("")) continue;
			parse();
			
			if(operator.equals("CD")) {
				cd();
			} else if(operator.equals("LIST")) {
				list();
			} else if(operator.equals("GET")) {
				get();
			} else if(operator.equals("PUT")) {
				put();
			} else if(operator.equals("QUIT")) {
				quit();
				break;
			} else {
				System.out.println("Type correctly");
				System.out.println("Supported command:");
				System.out.println("\t1. CD [server_dir]");
				System.out.println("\t2. LIST [server_dir]");
				System.out.println("\t3. GET [server_file] ");
				System.out.println("\t4. PUT [client_file]");
				System.out.println("To quit, type QUIT");
			}
		}
	}
	
	private void cd() throws IOException {
		String message;
		int statusCode;
		int responseLength;
		byte[] response;
		
		// send
		message = command + "\n";
		outToServer.write(message.getBytes("UTF-8"));
		
		// receive
		message = inFromServer.readLine();
		statusCode = Integer.parseInt(message);
		if(statusCode >= 0) {
			message = inFromServer.readLine();
			responseLength = Integer.parseInt(message);
			System.out.println(responseLength);
			response = new byte[responseLength];
			inFromServer.read(response, 0 , responseLength);
			message = new String(response, "UTF-8");
			System.out.println(message);
		} else {
			message = inFromServer.readLine();
			System.out.println(message);
		}
	}
	
	private void list() throws IOException {
		String message;
		int statusCode;
		int responseLength;
		byte[] response;
		String fileStr;
		int idx;

		// send
		message = command + "\n";
		outToServer.write(message.getBytes("UTF-8"));
		
		// receive
		message = inFromServer.readLine();
		statusCode = Integer.parseInt(message);
		if(statusCode >= 0) {
			message = inFromServer.readLine();
			responseLength = Integer.parseInt(message);
			response = new byte[responseLength];
			inFromServer.read(response, 0, responseLength);
			message = new String(response, "UTF-8");
			while(true) {
				idx = message.indexOf(',', message.indexOf(',') + 1);	// second ','
				if(idx == -1){
					System.out.println(message);
					break;
				} else {
					fileStr = message.substring(0, idx);
					message = message.substring(idx + 1);
					System.out.println(fileStr);
				}
			}
		} else {
			message = inFromServer.readLine();
			System.out.println(message);
		}
	}
	
	private void get() throws IOException {
		String message;
		int statusCode;
		FileOutputStream fout;
		File file;
		int fileSize;
		byte[] fileData;
		
		// send
		message = command + "\n";
		outToServer.write(message.getBytes("UTF-8"));

		// receive
		message = inFromServer.readLine();
		statusCode = Integer.parseInt(message);
		if(statusCode >= 0) {
			message = inFromServer.readLine();
			fileSize = Integer.parseInt(message);
			fileData = new byte[fileSize];
			inFromServer.read(fileData, 0, fileSize);
			
			file = new File(argument);
			if(file.exists()) {
				System.out.println("The file exists that has the same name.");
			} else {
				fout = new FileOutputStream(file);
				file.createNewFile();
				fout.write(fileData, 0, fileSize);
				fout.close();
				System.out.println("Received " + argument 
						+ " / " + fileSize 
						+ (fileSize<=1 ? " byte" : " bytes") );
			}
		} else {
			message = inFromServer.readLine();
			System.out.println(message);
		}
	}
	
	private void put() throws IOException {
		String message;
		String temp;
		int statusCode;
		int fileSize;
		FileInputStream fin;
		File file;
		byte[] header;
		byte[] fileData;
		byte[] byteMessage;
		
		// send
		message = command + "\n";
		file = new File(argument);
		
		if(file.exists()) {
			if(file.isDirectory()) {
				System.out.println("This file is a directory.");
				return;
			} else {
				fin = new FileInputStream(file);
				fileSize = (int)file.length();
				fileData = new byte[fileSize];
				fin.read(fileData, 0, fileSize);
				message = command + "\n"
						+ fileSize + "\n";
				header = message.getBytes("UTF-8");
				byteMessage = concatByteArrays(header, fileData);
				outToServer.write(byteMessage);
			}
		} else {
			System.out.println("Such file does not exists.");
			return;
		}
		
		// receive
		message = inFromServer.readLine();
		statusCode = Integer.parseInt(message);
		message = inFromServer.readLine();
		System.out.println(message);
	}
	
	private void quit() throws IOException {
		outToServer.writeBytes(operator + " \n");
	}
	
	private void parse() {
		int idx;
		
		idx = command.indexOf(' ');
		if(idx != -1) {
			operator = command.substring(0, idx);
			argument = command.substring(idx+1).trim();
		} else {
			operator = command;
			argument = "";
		}
		
		command = operator + " " + argument;
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

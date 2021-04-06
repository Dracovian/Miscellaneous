package handler;

import java.io.File;
import java.io.IOException;

import java.math.BigInteger;
import java.nio.file.Files;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Checksum {
	
	public Checksum() {}
	
	public String generateChecksum(File inputFile) throws NoSuchAlgorithmException, IOException {
		
		MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");
		
		if (!inputFile.exists() || !inputFile.isFile() || !inputFile.canRead())
			throw new IOException("Can\'t read file for hashing: " + inputFile.getAbsolutePath());
		
		else {
			byte[] fileContents = Files.readAllBytes(inputFile.toPath()),
				   fileChecksum = messageDigest.digest(fileContents);
			
			BigInteger checksum = new BigInteger(1, fileChecksum);
			return checksum.toString(16);
		}
	}

	public boolean checkFile(File inputFile, String checksum) throws NoSuchAlgorithmException, IOException {
		
		return checksum.equalsIgnoreCase(generateChecksum(inputFile));
	}
	
	public boolean compareFiles(File inputFile1, File inputFile2) throws NoSuchAlgorithmException, IOException {
		
		String checksum1 = generateChecksum(inputFile1),
			   checksum2 = generateChecksum(inputFile2);
		
		return checksum1.equalsIgnoreCase(checksum2);
	}
}

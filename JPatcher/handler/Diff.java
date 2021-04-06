package handler;

import java.io.ByteArrayOutputStream;

public class Diff {
	
	public Diff() {}
	
	public byte[] generateDiff(byte[] originalFileData, byte[] patchedFileData) {
		try {
			ByteArrayOutputStream originalFileBuffer = new ByteArrayOutputStream(),
					   patchedFileBuffer = new ByteArrayOutputStream(),
					   	 patchFileBuffer = new ByteArrayOutputStream();
			
			originalFileBuffer.write(originalFileData);
			 patchedFileBuffer.write( patchedFileData);
			 
			long originalFileSize = originalFileData.length,
				  patchedFileSize =  patchedFileData.length,
				  largestFileSize = originalFileSize > patchedFileSize ? originalFileSize : patchedFileSize,
				    patchDiffSize = originalFileSize > patchedFileSize ? originalFileSize - patchedFileSize : patchedFileSize - originalFileSize;

			if (originalFileSize > patchedFileSize)
				for (int i = 0; i < patchDiffSize; i++)
					patchedFileBuffer.write(0x00);
			
			else if (originalFileSize < patchedFileSize)
				for (int i = 0; i < patchDiffSize; i++)
					originalFileBuffer.write(0x00);
				
			byte[] originalFileDataBytes = originalFileBuffer.toByteArray(),
					patchedFileDataBytes =  patchedFileBuffer.toByteArray(),
					  patchFileDataBytes = new byte[(int) largestFileSize];
			
			for (int i = 0; i < largestFileSize; i++)
				patchFileDataBytes[i] = ((byte) (patchedFileDataBytes[i] ^ originalFileDataBytes[i]));
			
			patchFileBuffer.write(patchFileDataBytes);
			return patchFileBuffer.toByteArray();
			
		} catch (Exception e) {
			
			System.err.println(e.getMessage());
			return new byte[0];
		}
	}
	
	public byte[] mergeDiffs(byte[] originalFileData, byte[] patchFileData) {
		try {
			ByteArrayOutputStream originalFileBuffer = new ByteArrayOutputStream(),
					   patchedFileBuffer = new ByteArrayOutputStream(),
					   	 patchFileBuffer = new ByteArrayOutputStream();
			
			originalFileBuffer.write(originalFileData);
			   patchFileBuffer.write(   patchFileData);
			 
			long originalFileSize = originalFileData.length,
				    patchFileSize =    patchFileData.length,
				  largestFileSize = originalFileSize > patchFileSize ? originalFileSize : patchFileSize,
				    patchDiffSize = originalFileSize > patchFileSize ? originalFileSize - patchFileSize : patchFileSize - originalFileSize;

			if (originalFileSize > patchFileSize)
				for (int i = 0; i < patchDiffSize; i++)
					patchFileBuffer.write(0x00);
			
			else if (originalFileSize < patchFileSize)
				for (int i = 0; i < patchDiffSize; i++)
					originalFileBuffer.write(0x00);
				
			byte[] originalFileDataBytes = originalFileBuffer.toByteArray(),
					patchedFileDataBytes = new byte[(int) largestFileSize],
					  patchFileDataBytes =    patchFileBuffer.toByteArray();
			
			for (int i = 0; i < largestFileSize; i++)
				patchedFileDataBytes[i] = ((byte) (originalFileDataBytes[i] ^ patchFileDataBytes[i]));
			
			patchedFileBuffer.write(patchedFileDataBytes);
			return patchedFileBuffer.toByteArray();
			
		} catch (Exception e) {
			
			System.err.println(e.getMessage());
			return new byte[0];
		}
	}
}

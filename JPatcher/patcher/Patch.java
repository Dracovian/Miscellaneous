package patcher;

import java.io.File;
import java.io.RandomAccessFile;

import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;

import handler.Checksum;
import handler.Compressor;
import handler.Diff;

public class Patch {

	private RandomAccessFile originalFileAccess, patchedFileAccess, patchFileAccess;
	private MappedByteBuffer originalFileBuffer, patchedFileBuffer, patchFileBuffer;
	
	private byte[] originalFileBufferData, patchedFileBufferData, patchFileBufferDataCompressed;
	private long originalFileBufferSize, patchedFileBufferSize, patchFileBufferSizeCompressed;
	
	public Compressor compressor = new Compressor();
	public Checksum checksum = new Checksum();
	public Diff diff = new Diff();
	
	public Patch(String originalFileName, String patchedFileName) {
		try {
			originalFileAccess = new RandomAccessFile(new File(originalFileName), "r");
			 patchedFileAccess = new RandomAccessFile(new File( patchedFileName), "r");
			 
			FileChannel originalFileChannel = originalFileAccess.getChannel();
			FileChannel  patchedFileChannel =  patchedFileAccess.getChannel();
			
			originalFileBufferSize = originalFileChannel.size();
			 patchedFileBufferSize =  patchedFileChannel.size();
			 
			originalFileBuffer = originalFileChannel.map(FileChannel.MapMode.READ_ONLY, 0, originalFileBufferSize);
			 patchedFileBuffer =  patchedFileChannel.map(FileChannel.MapMode.READ_ONLY, 0,  patchedFileBufferSize);
			 
			if (originalFileBufferSize == 0 && patchedFileBufferSize == 0)
				throw new Exception("Empty input file buffers!");
			
			originalFileBufferData = new byte[(int) originalFileBufferSize];
			 patchedFileBufferData = new byte[(int)  patchedFileBufferSize];
			
			for (int i = 0; i < originalFileBufferSize; i++)
				originalFileBufferData[i] = originalFileBuffer.get(i);
			
			for (int i = 0; i < patchedFileBufferSize; i++)
				patchedFileBufferData[i] = patchedFileBuffer.get(i);
			
		} catch (Exception e) {
			
			System.err.println("\nRead Error: " + e.getMessage());
		}
	}
	
	public void createPatch(String patchFileName) {
		try {
			patchFileAccess = new RandomAccessFile(new File(patchFileName), "rw");
			FileChannel patchFileChannel = patchFileAccess.getChannel();
			
			patchFileBufferDataCompressed = compressor.compress(diff.generateDiff(originalFileBufferData, patchedFileBufferData));
			patchFileBufferSizeCompressed = patchFileBufferDataCompressed.length;
			
			patchFileBuffer = patchFileChannel.map(FileChannel.MapMode.READ_WRITE, 0, patchFileBufferSizeCompressed);
			for (byte diffByte : patchFileBufferDataCompressed) patchFileBuffer.put(diffByte);
			
		} catch (Exception e) {
			
			System.err.println("\nWrite Error: " + e.getMessage());
		}
	}
}

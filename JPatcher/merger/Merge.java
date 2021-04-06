package merger;

import java.io.File;
import java.io.RandomAccessFile;

import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;

import handler.Checksum;
import handler.Compressor;
import handler.Diff;

public class Merge {
	
	private RandomAccessFile originalFileAccess, patchedFileAccess, patchFileAccess;
	private MappedByteBuffer originalFileBuffer, patchedFileBuffer, patchFileBuffer;
	
	private byte[] originalFileBufferData, patchFileBufferData, patchFileBufferDataDecompressed;
	private long originalFileBufferSize, patchFileBufferSize;
	
	public Compressor compressor = new Compressor();
	public Checksum checksum = new Checksum();
	public Diff diff = new Diff();
	
	public Merge(String originalFileName, String patchFileName) {
		try {
			originalFileAccess = new RandomAccessFile(new File(originalFileName), "r");
			   patchFileAccess = new RandomAccessFile(new File(   patchFileName), "r");
			   
			 FileChannel originalFileChannel = originalFileAccess.getChannel();
			 FileChannel    patchFileChannel =    patchFileAccess.getChannel();
			 
			 originalFileBufferSize = originalFileChannel.size();
			    patchFileBufferSize =    patchFileChannel.size();
			    
			 originalFileBuffer = originalFileChannel.map(FileChannel.MapMode.READ_ONLY, 0, originalFileBufferSize);
			    patchFileBuffer =    patchFileChannel.map(FileChannel.MapMode.READ_ONLY, 0,    patchFileBufferSize);
			    
			 if (originalFileBufferSize == 0 && patchFileBufferSize == 0)
				 throw new Exception("Empty input file buffers!");
			 
			 originalFileBufferData = new byte[(int) originalFileBufferSize];
			    patchFileBufferData = new byte[(int)    patchFileBufferSize];
			    
			 for (int i = 0; i < originalFileBufferSize; i++)
				 originalFileBufferData[i] = originalFileBuffer.get(i);
			 
			 for (int i = 0; i < patchFileBufferSize; i++)
				 patchFileBufferData[i] = patchFileBuffer.get(i);
			 
			 patchFileBufferDataDecompressed = compressor.decompress(patchFileBufferData);
			
		} catch (Exception e) {
			
			System.err.println("\nRead Error: " + e.getMessage());
		}
	}
	
	public void mergePatch(String patchedFileName) {
		try {
			patchedFileAccess = new RandomAccessFile(new File(patchedFileName), "rw");
			
			FileChannel patchedFileChannel = patchedFileAccess.getChannel();
			patchedFileBuffer = patchedFileChannel.map(FileChannel.MapMode.READ_WRITE, 0, patchFileBufferSize);
			
			byte[] mergeBuffer = diff.mergeDiffs(originalFileBufferData, patchFileBufferDataDecompressed);
			for (byte mergeByte : mergeBuffer) patchedFileBuffer.put(mergeByte);
			
		} catch (Exception e) {
			
			System.err.println("\nWrite Error: " + e.getMessage());
		}
	}
}

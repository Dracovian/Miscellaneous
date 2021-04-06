package handler;

import java.io.IOException;

import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

public class Compressor {

	public Compressor() {}
	
	public byte[] compress(byte[] inputDataBytes) throws IOException {
		
		ByteArrayOutputStream inputData = new ByteArrayOutputStream(),
				             outputData = new ByteArrayOutputStream();
		
		inputData.write(inputDataBytes);
		GZIPOutputStream zipOutputStream = new GZIPOutputStream(outputData);
		
		for (byte inputByte : inputData.toByteArray())
			zipOutputStream.write(inputByte);
		
		zipOutputStream.finish();
		zipOutputStream.close();
		
		return outputData.toByteArray();
	}
	
	public byte[] decompress(byte[] inputDataBytes) throws IOException {
		
		
		ByteArrayOutputStream outputData = new ByteArrayOutputStream();
		ByteArrayInputStream inputStream = new ByteArrayInputStream(inputDataBytes);
		
		GZIPInputStream zipInputStream = new GZIPInputStream(inputStream);
		byte[] buffer = new byte[inputDataBytes.length]; int archiveSize;
		
		while ((archiveSize = zipInputStream.read(buffer)) != -1)
			outputData.write(buffer, 0, archiveSize);
		
		inputStream.close();
		zipInputStream.close();
		
		return outputData.toByteArray();
	}
}

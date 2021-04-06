package handler;

import merger.Merge;
import patcher.Patch;

public class Main {
	
	public static Merge merge;
	public static Patch patch;

	public static void main(String[] args) {
		if (args.length == 4) {
			String originalFileName = args[1];
			
			if (args[0].compareToIgnoreCase("patch") == 0) {
				String patchedFileName = args[2],
						 patchFileName = args[3];
				
				patch = new Patch(originalFileName, patchedFileName);
				patch.createPatch(patchFileName);
				
			} else if (args[0].compareToIgnoreCase("merge") == 0) {
				String patchedFileName = args[3],
						 patchFileName = args[2];
				
				merge = new Merge(originalFileName, patchFileName);
				merge.mergePatch(patchedFileName);
				
			}
		}
	}
}

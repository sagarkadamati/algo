package FileManager

import java.io.File

class MyFile(val path: String ?= null) {
	init {
		if (path != null) {
			File("./").walkTopDown().forEach {
				println(it)
			}		
		}
	}

	// fun setPath(path: String) {
		
	// }
}
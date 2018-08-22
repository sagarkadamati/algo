import java.io.File

class MyDir(val path: String ?= null) {
	init {
		if (path != null) {
			File("./").walkTopDown().forEach {
				println(it)
			}		
		}
	}
}

MyDir("./")
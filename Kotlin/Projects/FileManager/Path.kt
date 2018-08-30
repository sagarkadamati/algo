import java.io.File

class Path(str: String) {
	private var path: String = ""
	public val RECURSIVE: Boolean = true

	init {
		set(str)
	}

	fun get() : String {
		return this.path
	}

	fun set(pathStr: String) {
		this.path = pathStr
	}

	fun backward() {

	}

	fun forward(dir: String) {
		this.path += '\\' + dir
	}

	fun fixPath() {

	}

	fun getFiles(recursive: Boolean = false) {
		var dir = File(this.path).walkTopDown()
		if (!recursive) {
			dir.maxDepth(1).forEach {
				println(it)
			}
			return
		}

		dir.forEach {
			println(it)
		}
	}
}
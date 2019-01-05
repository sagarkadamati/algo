package MyAPI.FileManager

class MyFile(val path: String ?= null) {
	private var name = ""

	init {
	}

	fun rename(new: String) {
		this.name = new
	}
}
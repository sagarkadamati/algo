function AutoCompleteTest() {
	param(
		[Switch]$Data,
		[String]$Name
	)

	$Program = "AutoCompleteTest "
	foreach($key in $PSBoundParameters.Keys) {
		$AllArgs += "-"

		$AllArgs += $key
		$AllArgs += " "

		if ($PSBoundParameters[$key] -ne $True) {
			$AllArgs += $PSBoundParameters[$key]
			$AllArgs += " "
		}
	}

	$Program += AllArgs + $args
	Write-Host $AllArgs
}

function kt() {
	param(
		[Switch]$Werror,
		[Switch]$help,
		[Switch]$nowarn,
		[Switch]$verbose,
		[Switch]$version,

		[Switch]$Build,
		[Switch]$Run,
		[Switch]$Clean
	)

	if($Clean) {
		Remove-Item -Force app.jar
		return
	}

	if($Run) {
		$Program  = [System.IO.Path]::Combine($ToolsLocation, "Kotlin", "bin", "kotlin.bat app.jar")

		Invoke-Expression $Program
		return
	}

	$Program  = [System.IO.Path]::Combine($ToolsLocation, "Kotlin", "bin", "kotlinc.bat ")

	if ($Build) {
		$KTFiles = Get-FileNames -Recursive "kt$"
		foreach($KTFile in $KTFiles) {
			$AllArgs += " '$KTFile'"
		}
	}
	else {
		foreach($key in $PSBoundParameters.Keys) {
			$AllArgs += " -$key"
	
			if ($PSBoundParameters[$key] -ne $True) {
				$AllArgs += " '$PSBoundParameters[$key]'"
			}
		}
		$AllArgs += " $args"
	}

	$AllArgs += " -include-runtime"
	$AllArgs += " -kotlin-home '" + $([System.IO.Path]::Combine($ToolsLocation, "Kotlin")) + "'"
	$AllArgs += " -d app.jar"

	$Program += $AllArgs
	# $Program
	Invoke-Expression $Program
}

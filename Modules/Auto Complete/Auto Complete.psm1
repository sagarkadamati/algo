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
		[Switch]$Build,
		[Switch]$Run,
		[Switch]$Clean,

		[Switch]$Werror,
		[Switch]$help,
		[Switch]$nowarn,
		[Switch]$verbose,
		[Switch]$version
	)

	process
	{
		$APP = $((Get-Location).Path | Split-Path -Leaf) + ".jar"
		$APP = [System.IO.Path]::Combine($ToolsLocation, "Env", "Kotlin", "Bin", $APP)

		if($Clean) {
			Remove-Item -Force $App
			return
		}

		if($Run) {
			$Program  = [System.IO.Path]::Combine($ToolsLocation, "Kotlin", "bin", "kotlin.bat ")
			$Program += [System.IO.Path]::Combine($ToolsLocation, "Env", "Kotlin", "Bin", "$args.jar")

			# $Program
			Invoke-Expression $Program
			return
		}

		if (!$(Test-Path "Main.kt"))
		{
			Write-Host "Please Run in Project Root"
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
		$AllArgs += " -d " + $APP

		$Program += $AllArgs
		# $Program
		Invoke-Expression $Program
	}
}
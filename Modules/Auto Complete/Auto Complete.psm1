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
	param (
		[String]$Run,
		[String]$Build,
		[String]$Script,
		[String]$Clean
	)

		process
	{
		$Program  = "kotlinc "
		$BasePath = [System.IO.Path]::Combine($ToolsLocation, "Env", "Kotlin")

		CreateDirectory $(Join-Path $BasePath "Lib")
		CreateDirectory $(Join-Path $BasePath "Run")

		if(![string]::IsNullOrWhiteSpace($Run)) {
			# Write-Host "Running"

			$Program  = "kotlin "
			$Program += " -classpath '" + $(Join-Path $BasePath "Lib" | Join-Path -Child "*")
			$Program += "' -classpath '" + $(Join-Path $BasePath "Run" | Join-Path -Child "$Run.jar")
			$Program += "' MainKt"
			$Program += " '$Build' '$Script' '$Clean' $args"

			Invoke-Expression $Program
			return
		}

		if(![string]::IsNullOrWhiteSpace($Build)) {
			# Write-Host "Building: $Build $All $Clean"

			if ($Build -match '\*') {
				$Tasks = (Get-ChildItem -Directory -Path $(Join-Path $BasePath "Projects")).Name
				# $Tasks
			}
			else {
				$Tasks = $Build
			}

			CreateDirectory $(Join-Path $BasePath "Lib")
			CreateDirectory $(Join-Path $BasePath "Run")

			foreach ($Task in $Tasks) {
				$Program  = "kotlinc "
				Write-Host "Building $Task ... "
				$KTFiles = $(Get-ChildItem -Recurse -File -Path $(Join-Path $BasePath "Projects" | Join-Path -Child $Task)).FullName | Select-String -Pattern ".kt$"
				foreach($KTFile in $KTFiles) {
					$Program += " '$KTFile'"
				}

				if (Test-Path $(Join-Path $BasePath "Projects" | Join-Path -Child $Task | Join-Path -Child "Main.kt")) {
					$Program += " -include-runtime"
					$Program += " -d " + $(Join-Path $BasePath "Run" | Join-Path -Child "$Task.jar")
				}
				else {
					$Program += " -d " + $(Join-Path $BasePath "Lib" | Join-Path -Child "$Task.jar")
				}

				$Program += " -classpath " + $(Join-Path $BasePath "Lib" | Join-Path -Child "*")

				Invoke-Expression $Program
				Write-Host "done"
			}
			return
		}

		if(![string]::IsNullOrWhiteSpace($Clean)) {
			# Write-Host "Cleaning"

			if ($Clean -match '\*') {
				Write-Host "Cleaning All Tasks"
				Remove-Item -Force $(Join-Path $BasePath "Run" | Join-Path -Child "*") -ErrorAction Ignore
				Remove-Item -Force $(Join-Path $BasePath "Lib" | Join-Path -Child "*") -ErrorAction Ignore
			}
			else {
				Remove-Item -Force $(Join-Path $BasePath "Run" | Join-Path -Child "$Clean.jar") -ErrorAction Ignore
				Remove-Item -Force $(Join-Path $BasePath "Lib" | Join-Path -Child "$Clean.jar") -ErrorAction Ignore
			}
			return
		}

		if(![string]::IsNullOrWhiteSpace($Script)) {
			$Program += "-script "
			$Program += $(Join-Path $BasePath "Scripts" | Join-Path -Child "$Script.kts")
			$Program += " -classpath " + $(Join-Path $BasePath "Lib" | Join-Path -Child "*")

			# Write-Host "Running Script $Program"
			Invoke-Expression $Program
			return
		}

		$Program  = "kotlinc-jvm "
		$Program += " -classpath " + $(Join-Path $BasePath "Lib" | Join-Path -Child "*")
		Invoke-Expression $Program
	}
}

function Register-AutoComplete() {
	Register-ArgumentCompleter -CommandName kt -ScriptBlock {
		param($commandName, $parameterName, $wordToComplete, $commandAst, $fakeBoundParameter)

		if (($parameterName -like "*-Build*") -or ($parameterName -like "*-b*")) {
			$Projects = (Get-ChildItem -Directory -Path $([IO.Path]::Combine($ToolsLocation, "Env", "Kotlin", "Projects")) | Select-Object -ExpandProperty Name) -replace ".jar",""
			foreach ($Project in $Projects) {
				New-Object System.Management.Automation.CompletionResult($Project)
			}
			return
		}

		if (($parameterName -like "*-Clean*") -or ($parameterName -like "*-c*")) {
			$Runables = (Get-ChildItem -File -Path $([IO.Path]::Combine($ToolsLocation, "Env", "Kotlin", "Run")) | Select-Object -ExpandProperty Name) -replace ".jar",""
			foreach ($Runable in $Runables) {
				New-Object System.Management.Automation.CompletionResult($Runable)
			}

			$Libs = (Get-ChildItem -File -Path $([IO.Path]::Combine($ToolsLocation, "Env", "Kotlin", "Lib")) | Select-Object -ExpandProperty Name) -replace ".jar",""
			foreach ($Lib in $Libs) {
				New-Object System.Management.Automation.CompletionResult($Lib)
			}
			return
		}

		if (($parameterName -like "*-Script*") -or ($parameterName -like "*-s*")) {
			$Scripts = (Get-ChildItem -File -Path $([IO.Path]::Combine($ToolsLocation, "Env", "Kotlin", "Scripts")) | Select-Object -ExpandProperty Name) -replace ".kts",""
			foreach ($Script in $Scripts) {
				New-Object System.Management.Automation.CompletionResult($Script)
			}
			return
		}

		# if (($parameterName -like "*-Run*") -or ($parameterName -like "*-r*")) {
			$Runables = (Get-ChildItem -File -Path $([IO.Path]::Combine($ToolsLocation, "Env", "Kotlin", "Run")) | Select-Object -ExpandProperty Name) -replace ".jar",""
			foreach ($Runable in $Runables) {
				New-Object System.Management.Automation.CompletionResult($Runable)
			}
			return
			# }
		}

		Register-ArgumentCompleter -CommandName Proj -ScriptBlock {
			param($commandName, $parameterName, $wordToComplete, $commandAst, $fakeBoundParameter)

			$Projects = (Get-ChildItem -Directory -Path $ProjectsLocation | Select-Object -ExpandProperty Name)
			foreach ($Project in $Projects) {
				New-Object System.Management.Automation.CompletionResult("""" + $Project + """")
			}
		}
	}
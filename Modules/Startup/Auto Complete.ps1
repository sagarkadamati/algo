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
				New-Object System.Management.Automation.CompletionResult("-Name ")
			}
		}
	}
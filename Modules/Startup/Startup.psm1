function Prompt {
	$TEMP = $(Get-Date -UFormat "%H:%M") + " "

	$Location = $(Get-Location).path

	if ($WorkspaceLocation) {
		$PATTERN = $ProjectsLocation + "*"
		if ($Location -like $PATTERN) {
			$PROJ = $Location -split $("Projects")
			if ($PROJ[1]) {
				$TMP = $PROJ[1].split([IO.Path]::DirectorySeparatorChar)
				$TEMP += $TMP[1]
				if ($TMP[2]) {
 					$Location = $PROJ[1] | Split-Path -Leaf
				}
				else {
					$Location = "\\."
				}
			}
		}
	}

	$TEMP += "(" + $($Location | Split-Path -Leaf) + ")> "

	return $TEMP
}

function SetupEnv {
	Install-KeyHandlers
	Update-Theme
	Update-Paths
}

Export-ModuleMember -Function SetupEnv, Prompt

# New-Alias -Name gf -Value Get-Foo
# Export-ModuleMember -Function Get-Foo, New-Bar, ... -Alias gf, ...
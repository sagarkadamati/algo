
function ReplaceFileNames {
	param(
		[String]$FindStr,
		[String]$ReplaceWith,
		[String]$Delimiter,
		[Int]$Field
	)

	process {
		$Field--

		# Write-Host "$FindStr : $ReplaceWith : $Delimiter : $Field"
		foreach ($file in $(Get-ChildItem).Name) {
			if ($Field -ge 0) {
				if($Delimiter -like "") {
					$Delimiter = " "
				}

				$fields = $file -split $Delimiter
				if ($FindStr -like "") {
					$fields[$Field] = $ReplaceWith
				} else {
					if ($fields[$Field] -notlike "") {
						$fields[$Field] = ($fields[$Field]).Replace($FindStr, $ReplaceWith)
					}
				}

				$newFile = $fields -join $Delimiter
			} else {
				$newFile = $file.Replace($FindStr, $ReplaceWith)
			}

			if ($file -notlike $newFile) {
				if (($file -notlike "") -and ($newFile -notlike "")) {
					Write-Host $file "->" $newFile
					Move-Item  -literalpath $file $newFile -Force
				}
			}
		}
	}
}

function PrependFileNames($pstr) {
	foreach ($file in $(Get-ChildItem).Name) {
		$newFile = $pstr + $file
		if ($file -notlike $newFile) {
			Write-Host $file "->" $newFile
			Move-Item $file $newFile -Force
		}
	}
}

function Get-FileNames {
	param(
		[Switch]$Recursive,
		[String]$Pattern
	)

	process {
		if ($Recursive)
		{
			if ($Pattern)
			{
				((Get-ChildItem -File -recurse).FullName).Replace((Get-Location).Path + [IO.Path]::DirectorySeparatorChar, "") | Select-String -Pattern $Pattern
			}
			else
			{
				((Get-ChildItem -File -recurse).FullName).Replace((Get-Location).Path + [IO.Path]::DirectorySeparatorChar, "")
			}
		}
		else
		{
			if ($Pattern)
			{
				(Get-ChildItem -File).Name | Select-String -Pattern $Pattern
			}
			else
			{
				(Get-ChildItem -File).Name
			}
		}
	}
}

function Get-Matches {
	param(
		[Switch]$Recursive,
		[String]$InputString
	)

	process {
		if ($Recursive)
		{
			$Pattern = [regex]::Escape($InputString)
			Get-FileNames -Recursive | foreach { Select-String -LiteralPath $_ -Pattern $Pattern}
		}
		else
		{
			Get-FileNames | foreach { Select-String -LiteralPath $_ -Pattern $Pattern }
		}
	}
}

function StringSplitCaps($Str) {
	return ($Str.substring(0,1).toupper() + $Str.substring(1) -creplace '[A-Z]', ' $&').Trim();
}

function TrimFileName {
	foreach ($file in $(Get-ChildItem).Name) {
		$Fields = $file -split " "
		$newFile = $Fields[0]
		$newFile += " "
		$newFile += $Fields[1]
		$newFile += ".mp4"
		if ($file -notlike $newFile) {
			Write-Host $file "->" $newFile
			Move-Item $file $newFile -Force
		}
	}
}

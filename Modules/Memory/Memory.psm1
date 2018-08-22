
function ReplaceFileNames($ostr, $nstr) {
	foreach ($file in $(Get-ChildItem).Name) {
		$newFile = $file.Replace($ostr, $nstr)
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

function Get-Json {
	param(
		[String]$File
	)
	process {
		Get-Content $File | ConvertFrom-Json
	}
}

function StringSplitCaps($Str) {
	return ($Str.substring(0,1).toupper() + $Str.substring(1) -creplace '[A-Z]', ' $&').Trim();
}
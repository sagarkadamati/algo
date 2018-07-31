
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
		[Switch]$Recursive
	)

	process {
		if ($Recursive)
		{
			((Get-ChildItem -File -recurse).FullName).Replace((Get-Location).Path + [IO.Path]::DirectorySeparatorChar, "")
		}
		else
		{
			(Get-ChildItem -File).Name
		}
	}
}

function Get-Matches {
	param(
		[Switch]$Recursive,
		[String]$Pattern
	)

	process {
		if ($Recursive)
		{
			# (Get-FileNames -Recursive | foreach { Select-String -LiteralPath $_ -Pattern $Pattern } | Out-String).Trim()
			Get-FileNames -Recursive | foreach { Select-String -LiteralPath $_ -Pattern $Pattern }
		}
		else
		{
			Get-FileNames | foreach { Select-String -LiteralPath $_ -Pattern $Pattern }
		}
	}
}
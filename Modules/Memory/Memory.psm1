
function ReplaceFileNames($ostr, $nstr) {
	foreach ($file in $(Get-ChildItem).Name) {
		$newFile = $file.Replace($ostr, $nstr)
		if ($file -notlike $newFile) {
			Write-Host $file "->" $newFile
			Move-Item $file $newFile -Force
		}
	}
}
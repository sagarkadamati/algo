Function Get-Foo {
	Write-Host "Get-Foo"
}

Function Set-Bar {
	Write-Host "Set-Foo"
}

New-Alias -Name gf -Value Get-Foo

Export-ModuleMember -Function Get-Foo, New-Bar, ... -Alias gf, ...
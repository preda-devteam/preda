param(
    [Parameter()]
    [string]$ExtensionPath
)
$Candidates = @(
    "HKCU:SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\{771FD6B0-FA20-440A-A002-3B3BAC16DC50}_is1",
    "HKCU:SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\{D628A17A-9713-46BF-8D57-E671B46A741E}_is1",
    "HKLM:SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall\{F8A2A208-72B3-4D61-95FC-8A65D340689B}_is1",
    "HKLM:SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\{EA457B21-F73E-494C-ACAB-524FDE069978}_is1"
)
$VSCodeLocation = ""
Foreach ($Candidate in $Candidates) {
    try{
        $VSCodeLocation = Get-ItemPropertyValue -Path $Candidate -Name InstallLocation -ErrorAction Stop
    }
    catch [System.Management.Automation.ItemNotFoundException] {
        Continue
    }
}
$Helper = $VSCodeLocation + "resources\app\out\cli.js"
$VSCode = $VSCodeLocation + "Code.exe"
$Command = 'set ELECTRON_RUN_AS_NODE=1 && "{0}" "{1}" --ms-enable-electron-run-as-node --install-extension "{2}"' -f $VSCode, $Helper, $ExtensionPath
& "C:\Windows\system32\cmd.exe" /v /c $Command
exit $LASTEXITCODE
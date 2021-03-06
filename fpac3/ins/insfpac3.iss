; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "FPac 3"
#define MyAppVersion "1.3.1.3"
#define MyAppPublisher "Patquoi.fr"
#define MyAppURL "http://patquoi.fr"
#define MyAppExeName "fpac3.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{3AE59C12-81ED-4725-920B-6A769F80CD12}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppPublisher}\{#MyAppName}
DefaultGroupName={#MyAppPublisher}\{#MyAppName}
UninstallDisplayIcon={app}\Uninstall.ico
UninstallDisplayName={#MyAppName}
LicenseFile=..\bin\licence.txt
InfoBeforeFile=..\bin\Lisezmoi.txt
InfoAfterFile=..\bin\Lisezmoi.txt
WizardImageFile=fpac3.bmp
WizardSmallImageFile=icone.bmp
OutputDir="C:\Users\Patrice Fouquet\Documents\Embarcadero\Studio\Projets\fpac3\ins\Output"
OutputBaseFilename=insfpac3
SetupIconFile="C:\Users\Patrice Fouquet\Documents\Embarcadero\Studio\Projets\fpac3\ins\fpac3@256.ico"
AppComments=Pacman en quadriptyque
AppContact=fpac3@patquoi.fr
Compression=lzma
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64
VersionInfoVersion={#MyAppVersion}

[Languages]
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; IconFilename: "{app}\{#MyAppExeName}"; IconIndex: 0; Flags: createonlyiffileexists useapppaths
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"; IconFilename: "{app}\Uninstall.ico"; Comment: "D�sinstalle FPac 3"; IconIndex: 0
Name: "{group}\Lisez-Moi (FPac 3)"; Filename: "{app}\Lisezmoi.txt"; WorkingDir: "{app}"; Comment: "Fichier lisez-moi � lire en premier !"
Name: "{group}\Sources de Fpac 3"; Filename: "{app}\fpac3-src-win64.zip"; Comment: "Code source de FPac 3"

[Run]
Filename: "{app}\impcfgfpac3.exe"; Parameters: """{app}"""; Description: "Importer une configuration d�j� existante"; Flags: postinstall skipifsilent
Filename: "{app}\Lisezmoi.txt"; Description: "Lisez-moi !"; Flags: postinstall shellexec skipifsilent
Filename: "{app}\{#MyAppExeName}"; Description: "Jouer � FPac 3 !"; Flags: postinstall nowait skipifsilent

[Files]
Source: "..\bin\fpac3.64.exe"; DestDir: "{app}"; DestName: "fpac3.exe"; Check: Is64BitInstallMode; Flags: ignoreversion
Source: "..\bin\fpac3.32.exe"; DestDir: "{app}"; DestName: "fpac3.exe"; Check: not Is64BitInstallMode; Flags: solidbreak ignoreversion
Source: "..\bin\licence.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\license.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\Lisezmoi.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\impcfgfpac3\bin\impcfgfpac3.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\ins\Uninstall.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\fpac3-src-win64.zip"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files


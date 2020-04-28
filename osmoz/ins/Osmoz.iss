; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Osmoz�"
#define MyAppVersion "4.6.0.5"
#define MyAppPublisher "Patquoi.fr"
#define MyAppURL "http://patquoi.fr"
#define MyAppExeName "osmoz.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{4521DB68-1EA9-4612-A4FD-F0D6A8A17855}
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
LicenseFile="..\bin\licence.txt"
InfoBeforeFile="..\bin\lisezmoi.txt"
InfoAfterFile="..\bin\licence.txt"
WizardImageFile=grande.bmp
WizardSmallImageFile=petite.bmp
OutputDir="..\ins\Output"
OutputBaseFilename=insosmoz
SetupIconFile="..\ins\Osmoz.ico"
AppComments=Etendez votre territoire et partez � la conqu�te des mots adverses !
AppContact=osmoz@patquoi.fr
Compression=lzma
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64
VersionInfoVersion={#MyAppVersion}
                                  
[Languages]
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Registry]
Root: HKCR; SubKey: ".sm�"; ValueType: string; ValueData: "Sm�";
Root: HKCR; SubKey: "Sm�"; ValueType: string; ValueData: "Partie d'Osmoz�";
Root: HKCR; SubKey: "Sm�\DefaultIcon"; ValueType: string; ValueData: "{app}\bin\{#MyAppExeName},0";
Root: HKCR; SubKey: "Sm�\shell\open\command"; ValueType: string; ValueData: "{app}\bin\{#MyAppExeName} ""%1""";

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\bin\{#MyAppExeName}"; IconFilename: "{app}\bin\{#MyAppExeName}"; IconIndex: 0; Flags: createonlyiffileexists useapppaths
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"; IconFilename: "{app}\Uninstall.ico"; Comment: "D�sinstalle Osmoz"; IconIndex: 0
Name: "{group}\Lisez-Moi (Osmoz)"; Filename: "{app}\Lisezmoi.txt"; WorkingDir: "{app}"; Comment: "Fichier lisez-moi � lire en premier !"
Name: "{group}\Sources d'Osmoz"; Filename: "{app}\osmoz-src-win64.zip"; Comment: "Code source d'Osmoz"
Name: "{group}\Aide (Osmoz)"; Filename: "{app}\bin\html\Osmoz.html"; WorkingDir: "{app}\bin\html"; Comment: "Aide HTML d'Osmoz"

[Run]
Filename: "{app}\Lisezmoi.txt"; Description: "Lisez-moi !"; Flags: postinstall shellexec skipifsilent
Filename: "{app}\bin\{#MyAppExeName}"; Description: "Lancer Osmotik !"; Flags: postinstall nowait skipifsilent


[Files]
Source: "..\bin\licence.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\license.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\lisezmoi.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "Uninstall.ico"; DestDir: "{app}"; Flags: Ignoreversion
Source: "..\bin\osmoz.64.exe"; DestDir: "{app}\bin"; DestName: {#MyAppExeName}; Check: Is64BitInstallMode; Flags: ignoreversion
Source: "..\bin\osmoz.32.exe"; DestDir: "{app}\bin"; DestName: {#MyAppExeName}; Check: not Is64BitInstallMode; Flags: solidbreak ignoreversion
Source: "..\bin\L23456789ABCDEF"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\osmoz-src-win64.zip"; DestDir: "{app}"; Flags: Ignoreversion
Source: "..\bin\html\decompte.png"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\deplt.png"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\fondhexa.png"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\joueurs.png"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\osmoz.html"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\osmoz.png"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\params.png"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\plateau.png"; DestDir: "{app}\bin\html"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files


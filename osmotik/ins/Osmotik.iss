; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Osmotik"
#define MyAppVersion "1.4.0.17"
#define MyAppPublisher "Patquoi.fr"
#define MyAppURL "http://patquoi.fr/#osmotik"
#define MyAppExeName "osmotik.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{E5982670-115B-4496-BA22-0D0DF0C3AC45}
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
LicenseFile="C:\Users\Patrice Fouquet\Documents\Embarcadero\Studio\Projets\Osmotik\bin\licence.txt"
InfoBeforeFile="C:\Users\Patrice Fouquet\Documents\Embarcadero\Studio\Projets\Osmotik\bin\lisezmoi.txt"
InfoAfterFile="C:\Users\Patrice Fouquet\Documents\Embarcadero\Studio\Projets\Osmotik\bin\lisezmoi.txt"
WizardImageFile=Osm.bmp
WizardSmallImageFile=Smtk.bmp
OutputDir="C:\Users\Patrice Fouquet\Documents\Embarcadero\Studio\Projets\Osmotik\ins\output"
OutputBaseFilename=insosmotik
SetupIconFile="C:\Users\Patrice Fouquet\Documents\Embarcadero\Studio\Projets\Osmotik\ins\osmotik.ico"
AppComments=Etendez votre territoire et partez � la conqu�te des mots adverses !
AppContact=osmotik@patquoi.fr
Compression=lzma
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64
VersionInfoVersion={#MyAppVersion}
   
[Languages]
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Registry]
Root: HKCR; SubKey: ".smt"; ValueType: string; ValueData: "Smt";
Root: HKCR; SubKey: "Smt"; ValueType: string; ValueData: "Partie d'Osmotik";
Root: HKCR; SubKey: "Smt\DefaultIcon"; ValueType: string; ValueData: "{app}\bin\{#MyAppExeName},1";
Root: HKCR; SubKey: "Smt\shell\open\command"; ValueType: string; ValueData: "{app}\bin\{#MyAppExeName} ""%1""";

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\bin\{#MyAppExeName}"; IconFilename: "{app}\bin\{#MyAppExeName}"; IconIndex: 0; Flags: createonlyiffileexists useapppaths
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"; IconFilename: "{app}\Uninstall.ico"; Comment: "D�sinstalle Osmotik"; IconIndex: 0
Name: "{group}\Lisez-Moi (Osmotik)"; Filename: "{app}\Lisezmoi.txt"; WorkingDir: "{app}"; Comment: "Fichier lisez-moi � lire en premier !"
Name: "{group}\Sources d'Osmotik"; Filename: "{app}\osmtk-src-win64.zip"; Comment: "Code source d'Osmotik"
Name: "{group}\Aide (Osmotik)"; Filename: "{app}\bin\html\Osmotik.html"; WorkingDir: "{app}\bin\html"; Comment: "Aide HTML d'Osmotik"

[Run]
Filename: "{app}\Lisezmoi.txt"; Description: "Lisez-moi !"; Flags: postinstall shellexec skipifsilent
Filename: "{app}\bin\{#MyAppExeName}"; Description: "Lancer Osmotik !"; Flags: postinstall nowait skipifsilent


[Files]
Source: "..\bin\lisezmoi.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\licence.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\license.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "Uninstall.ico"; DestDir: "{app}"; Flags: Ignoreversion
Source: "..\bin\osmotik.64.exe"; DestDir: "{app}\bin"; DestName: {#MyAppExeName}; Check: Is64BitInstallMode; Flags: ignoreversion
Source: "..\bin\osmotik.32.exe"; DestDir: "{app}\bin"; DestName: {#MyAppExeName}; Check: not Is64BitInstallMode; Flags: solidbreak ignoreversion
Source: "..\bin\L23456789ABCDEF"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\osmtk-src-win64.zip"; DestDir: "{app}"; Flags: Ignoreversion
Source: "..\bin\html\beurre0.gif"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\beurre1.gif"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\beurre2.gif"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\beurre3.gif"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\beurre4.gif"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\beurre5.gif"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\epave.gif"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\findetour.gif"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\fondhexa.jpg"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\nouvelle.jpg"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\Osmotik.gif"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\osmotik.html"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\placement.gif"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\plateau.gif"; DestDir: "{app}\bin\html"; Flags: ignoreversion
Source: "..\bin\html\scores.gif"; DestDir: "{app}\bin\html"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files


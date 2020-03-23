unit prmbus_f;

interface

uses
  SysUtils, Types, Classes, Variants, QGraphics, QControls, QForms, QDialogs,
  QStdCtrls, QExtCtrls, QComCtrls, QMenus, QTypes;

type
  TfrmParamBus = class(TForm)
    GroupBox1: TGroupBox;
    LabelNbArretsBus: TLabel;
    Label2: TLabel;
    Label4: TLabel;
    LabelNbBus: TLabel;
    Label3: TLabel;
    LabelNbMaxArretsBus: TLabel;
    ButtonOk: TButton;
    ButtonAnnuler: TButton;
    ButtonAppliquer: TButton;
    LabelLigne: TLabel;
    LabelArrets: TLabel;
    LabelNumerosArrets: TLabel;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    CheckBox3: TCheckBox;
    CheckBox4: TCheckBox;
    CheckBox5: TCheckBox;
    CheckBox6: TCheckBox;
    CheckBox7: TCheckBox;
    CheckBox8: TCheckBox;
    CheckBox9: TCheckBox;
    CheckBoxTout: TCheckBox;
    Shape1: TShape;
    LabelL1: TLabel;
    Shape2: TShape;
    LabelL2: TLabel;
    Shape3: TShape;
    LabelL3: TLabel;
    Shape4: TShape;
    LabelL4: TLabel;
    Shape5: TShape;
    LabelL5: TLabel;
    Shape6: TShape;
    LabelL6: TLabel;
    Shape7: TShape;
    LabelL7: TLabel;
    Shape8: TShape;
    LabelL8: TLabel;
    Shape9: TShape;
    LabelL9: TLabel;
    ShapeT: TShape;
    LabelT: TLabel;
    SpinEdit1: TSpinEdit;
    SpinEdit2: TSpinEdit;
    SpinEdit3: TSpinEdit;
    SpinEdit4: TSpinEdit;
    SpinEdit5: TSpinEdit;
    SpinEdit6: TSpinEdit;
    SpinEdit7: TSpinEdit;
    SpinEdit8: TSpinEdit;
    SpinEdit9: TSpinEdit;
    SpinEdit11: TSpinEdit;
    SpinEdit12: TSpinEdit;
    SpinEdit13: TSpinEdit;
    SpinEdit14: TSpinEdit;
    SpinEdit15: TSpinEdit;
    SpinEdit16: TSpinEdit;
    SpinEdit17: TSpinEdit;
    SpinEdit18: TSpinEdit;
    SpinEdit19: TSpinEdit;
    SpinEdit21: TSpinEdit;
    SpinEdit22: TSpinEdit;
    SpinEdit23: TSpinEdit;
    SpinEdit24: TSpinEdit;
    SpinEdit25: TSpinEdit;
    SpinEdit26: TSpinEdit;
    SpinEdit27: TSpinEdit;
    SpinEdit28: TSpinEdit;
    SpinEdit29: TSpinEdit;
    SpinEdit31: TSpinEdit;
    SpinEdit32: TSpinEdit;
    SpinEdit33: TSpinEdit;
    SpinEdit34: TSpinEdit;
    SpinEdit35: TSpinEdit;
    SpinEdit36: TSpinEdit;
    SpinEdit37: TSpinEdit;
    SpinEdit38: TSpinEdit;
    SpinEdit39: TSpinEdit;
    SpinEdit41: TSpinEdit;
    SpinEdit42: TSpinEdit;
    SpinEdit43: TSpinEdit;
    SpinEdit44: TSpinEdit;
    SpinEdit45: TSpinEdit;
    SpinEdit46: TSpinEdit;
    SpinEdit47: TSpinEdit;
    SpinEdit48: TSpinEdit;
    SpinEdit49: TSpinEdit;
    SpinEdit51: TSpinEdit;
    SpinEdit52: TSpinEdit;
    SpinEdit53: TSpinEdit;
    SpinEdit54: TSpinEdit;
    SpinEdit55: TSpinEdit;
    SpinEdit56: TSpinEdit;
    SpinEdit57: TSpinEdit;
    SpinEdit58: TSpinEdit;
    SpinEdit59: TSpinEdit;
    SpinEdit61: TSpinEdit;
    SpinEdit62: TSpinEdit;
    SpinEdit63: TSpinEdit;
    SpinEdit64: TSpinEdit;
    SpinEdit65: TSpinEdit;
    SpinEdit66: TSpinEdit;
    SpinEdit67: TSpinEdit;
    SpinEdit68: TSpinEdit;
    SpinEdit69: TSpinEdit;
    SpinEdit71: TSpinEdit;
    SpinEdit72: TSpinEdit;
    SpinEdit73: TSpinEdit;
    SpinEdit74: TSpinEdit;
    SpinEdit75: TSpinEdit;
    SpinEdit76: TSpinEdit;
    SpinEdit77: TSpinEdit;
    SpinEdit78: TSpinEdit;
    SpinEdit79: TSpinEdit;
    SpinEdit81: TSpinEdit;
    SpinEdit82: TSpinEdit;
    SpinEdit83: TSpinEdit;
    SpinEdit84: TSpinEdit;
    SpinEdit85: TSpinEdit;
    SpinEdit86: TSpinEdit;
    SpinEdit87: TSpinEdit;
    SpinEdit88: TSpinEdit;
    SpinEdit89: TSpinEdit;
    SpinEdit91: TSpinEdit;
    SpinEdit92: TSpinEdit;
    SpinEdit93: TSpinEdit;
    SpinEdit94: TSpinEdit;
    SpinEdit95: TSpinEdit;
    SpinEdit96: TSpinEdit;
    SpinEdit97: TSpinEdit;
    SpinEdit98: TSpinEdit;
    SpinEdit99: TSpinEdit;
    LabelRq1: TLabel;
    LabelRq3: TLabel;
    LabelRqCochesLignesBus: TLabel;
    GroupBox2: TGroupBox;
    Label9: TLabel;
    SpinEditNbMaxPersonnesBus: TSpinEdit;
    Label10: TLabel;
    Label11: TLabel;
    SpinEditNbToursStopArretBus: TSpinEdit;
    Label12: TLabel;
    GroupBox3: TGroupBox;
    Label13: TLabel;
    SpinEditNbCasesMaxArretBus: TSpinEdit;
    Label14: TLabel;
    Label15: TLabel;
    SpinEditProbaDirArretBus: TSpinEdit;
    Label16: TLabel;
    Label17: TLabel;
    SpinEditNbMaxToursAttenteBus: TSpinEdit;
    Label18: TLabel;
    Label19: TLabel;
    SpinEditProbaArretDmd: TSpinEdit;
    Label20: TLabel;
    TimerClignotement: TTimer;
    PopupMenu: TPopupMenu;
    procedure FormShow(Sender: TObject);
    procedure SpinEditChanged(Sender: TObject; NewValue: Integer);
    procedure TimerClignotementTimer(Sender: TObject);
    procedure ButtonOkClick(Sender: TObject);
    procedure ButtonAppliquerClick(Sender: TObject);
    procedure SpinEditParametresChanged(Sender: TObject;
      NewValue: Integer);
    procedure CheckBoxClick(Sender: TObject);
    procedure CheckBoxToutClick(Sender: TObject);
    procedure FormResize(Sender: TObject);
  private
    NbArretsBus : Integer;
    InitialisationEnCours : Boolean;
    procedure RafraichitNbBus;
    function AppliqueChoix : Boolean;
  public
    NumArretBusAMontrer : Integer;
  end;

var
  frmParamBus: TfrmParamBus;

implementation

uses Math, simul, prmsim_f, simul_f;

{$R *.xfm}

const stOrdre : array [0..1] of String = ('ème', 'er');
//---------------------------------------------------------------------------
procedure TfrmParamBus.RafraichitNbBus;
var i, NbBus : Integer;
 begin
  NbBus:=0;
  for i:=0 to NBMAXLIGNESBUS-1 do
   if cv.LignesBus[i].NbArrets>0 then
    Inc(NbBus, 1+(cv.LignesBus[i].NbArrets-1) div 3); // On a 1 bus pour 1 à 3 arrêts ; 2 pour 4 à 6 et 3 pour 7 à 9.
  LabelNbBus.Caption:=IntToStr(NbBus);
 end;
//---------------------------------------------------------------------------
procedure TfrmParamBus.FormShow(Sender: TObject);
var i, j : Integer;
    stNumLigne : String;
    SpinEdit : TSpinEdit;
    Shape : TShape;
begin
 NumArretBusAMontrer:=0;
 InitialisationEnCours:=true;
 NbArretsBus:=0;
 for i:=0 to cv.NbArretsBus-1 do
  Inc(NbArretsBus, Ord(cv.ArretsBus[i].Defini));
  LabelNbArretsBus.Caption:=IntToStr(NbArretsBus);
  LabelNbMaxArretsBus.Caption:=IntToStr(cv.NbArretsBus);
  RafraichitNbBus;
  if NbArretsBus>0 then
   begin
    CheckBoxTout.Visible:=(cv.TourCrt>0);
    LabelT.Visible:=(cv.TourCrt>0);
    ShapeT.Visible:=(cv.TourCrt>0);
    if cv.TourCrt=0 then
     begin
      LabelLigne.Caption:='Ligne';
      LabelLigne.Left:=LabelLigne.Left+8;
     end;
    LabelRqCochesLignesBus.Visible:=(cv.TourCrt>0);
    for i:=1 to NBMAXLIGNESBUS do
     begin
      SpinEdit:=FindComponent('SpinEdit'+IntToStr(i)) as TSpinEdit;
      if cv.NbArretsBus<NBMAXARRETSBUSPARLIGNE then
       SpinEdit.Max:=cv.NbArretsBus;
      SpinEdit.Value:=cv.LignesBus[i-1].NbArrets;
      SpinEdit.Enabled:=(cv.TourCrt=0);
      (FindComponent('CheckBox'+IntToStr(i)) as TCheckBox).Visible:=(cv.TourCrt>0) and (cv.LignesBus[i-1].NbArrets>0);
      for j:=1 to NBMAXARRETSBUSPARLIGNE do
       begin
        SpinEdit:=FindComponent('SpinEdit'+IntToStr(10*i+j)) as TSpinEdit;
        SpinEdit.Max:=cv.NbArretsBus;
        SpinEdit.Value:=cv.LignesBus[i-1].NumArret[j-1];
        SpinEdit.Enabled:=(cv.TourCrt=0);
       end{for j};
      stNumLigne:=IntToStr(i);
      Shape:=FindComponent('Shape'+stNumLigne) as TShape;
      Shape.Brush.Color:=CoulLigneBus[i-1];
      Shape.Pen.Color:=CoulLigneBus[i-1];
      (FindComponent('LabelL'+stNumLigne) as TLabel).Font.Color:=CoulTLigneBus[i-1];
     end{for i};
   end{if NbArretsBus>0}
  else
   begin
    for i:=1 to NBMAXLIGNESBUS do
     (FindComponent('SpinEdit'+IntToStr(i)) as TSpinEdit).Visible:=false;
    Application.MessageBox( 'Vous devez poser au moins un arrêt de bus sur le réseau pour pouvoir définir le réseau de lignes de bus.',
                            'Impossible de paramétrer le réseau de lignes de bus', [smbOk], smsWarning);
   end;
  SpinEditNbMaxPersonnesBus.Value:=cv.NbMaxPersonnesBus;
  SpinEditNbToursStopArretBus.Value:=cv.NbToursStopArretBus;
  SpinEditNbCasesMaxArretBus.Value:=cv.NbMaxCasesDetectArretBus;
  SpinEditProbaDirArretBus.Value:=cv.ProbaDirArretBus;
  SpinEditNbMaxToursAttenteBus.Value:=cv.NbMaxToursAttenteBus;
  SpinEditProbaArretDmd.Value:=cv.ProbaArretBusDmd;
  InitialisationEnCours:=false;
end;
//---------------------------------------------------------------------------
function TfrmParamBus.AppliqueChoix : Boolean;
var stMsg : String;
    i, j : Integer;
    SpinEditNb, SpinEditNum : TSpinEdit;
 begin
  // 1. On vérifie que tous les arrêts sont définis
  for i:=1 to NBMAXLIGNESBUS do
   begin
    SpinEditNb:=FindComponent('SpinEdit'+IntToStr(i)) as TSpinEdit;
    if SpinEditNb.Value>0 then
     begin
      for j:=1 to SpinEditNb.Value do
       begin
        SpinEditNum:=FindComponent('SpinEdit'+IntToStr(10*i+j)) as TSpinEdit;
        if SpinEditNum.Value=0 then
         stMsg:= stMsg+
                 Format( ' - Le %d%s arrêt de ligne n°%d n''est pas défini.'#13#10,
                         [j, stOrdre[Ord(j=1)], i]);
       end{for j};
     end;
   end{for i};
  if stMsg<>'' then
   begin
    Application.MessageBox( 'Le réseau de bus n''est pas correct :'#13#10+stMsg+#13#10'Corrigez avant de continuer.',
                            'Impossible de continuer', [smbOk], smsWarning);
    Result:=false;
    Exit;
   end;
  // 2. On valide les lignes de bus
  frmSimulation.SimulModifiee:=true;
  cv.InitialiseInfosLignesBus;
  for i:=1 to NBMAXLIGNESBUS do
   begin
    SpinEditNb:=FindComponent('SpinEdit'+IntToStr(i)) as TSpinEdit;
    cv.LignesBus[i-1].NbArrets:=SpinEditNb.Value;
    if SpinEditNb.Value>0 then
     begin
      Inc(cv.NbLignesBus);
      for j:=1 to SpinEditNb.Value do
       begin
        SpinEditNum:=FindComponent('SpinEdit'+IntToStr(10*i+j)) as TSpinEdit;
        cv.LignesBus[i-1].NumArret[j-1]:=SpinEditNum.Value;
        cv.ArretsBus[SpinEditNum.Value-1].AjouteLigneBus(i);
       end{for j};
     end;
   end{for i};
  // 3. On valide les autres paramètres
  cv.NbMaxPersonnesBus:=SpinEditNbMaxPersonnesBus.Value;
  cv.NbToursStopArretBus:=SpinEditNbToursStopArretBus.Value;
  cv.NbMaxCasesDetectArretBus:=SpinEditNbCasesMaxArretBus.Value;
  cv.ProbaDirArretBus:=SpinEditProbaDirArretBus.Value;
  cv.NbMaxToursAttenteBus:=SpinEditNbMaxToursAttenteBus.Value;
  cv.ProbaArretBusDmd:=SpinEditProbaArretDmd.Value;
  ButtonAppliquer.Enabled:=false;
  RafraichitNbBus;
  Result:=true;
 end;
//---------------------------------------------------------------------------
procedure TfrmParamBus.SpinEditChanged(Sender: TObject;
  NewValue: Integer);
var SpinEdit : TSpinEdit;
    i, k, n, AncNumArretBusAMontrer : Integer;
begin
 SpinEdit:=Sender as TSpinEdit;
 k:=StrToInt(copy(SpinEdit.Name, 9, Length(SpinEdit.Name)-8));
 n:=NewValue;
 if k div 10=0 then
  for i:=1 to NBMAXARRETSBUSPARLIGNE do
   (FindComponent('SpinEdit'+IntToStr(10*k+i)) as TSpinEdit).Visible:=(i<=n)
 else  // N° arrêt de bus
  if (n=0) or (n>cv.NbArretsBus) then
   SpinEdit.Value:=0
  else
   if not cv.ArretsBus[n-1].Defini then
    SpinEdit.Value:=1+SpinEdit.Value mod cv.NbArretsBus
   else
    if not InitialisationEnCours then
     begin
      AncNumArretBusAMontrer:=NumArretBusAMontrer;
      if NumArretBusAMontrer>0 then
       begin
        NumArretBusAMontrer:=0;
        cv.v[ cv.ArretsBus[AncNumArretBusAMontrer-1].x,
              cv.ArretsBus[AncNumArretBusAMontrer-1].y].RedessineCasesArretBus(indefinie);
       end;
      NumArretBusAMontrer:=SpinEdit.Value;
      // On bouge le curseur pour être sûr de voir l'arrêt
      frmSimulation.DrawGridSimul.Col:=cv.ArretsBus[NumArretBusAMontrer-1].x;
      frmSimulation.DrawGridSimul.Row:=cv.ArretsBus[NumArretBusAMontrer-1].y;
     end;
 if not InitialisationEnCours then ButtonAppliquer.Enabled:=true;
end;
//---------------------------------------------------------------------------
procedure TfrmParamBus.TimerClignotementTimer(Sender: TObject);
begin
 TimerClignotement.Tag:=1-TimerClignotement.Tag;
 if NumArretBusAMontrer>0 then
   cv.v[ cv.ArretsBus[NumArretBusAMontrer-1].x,
         cv.ArretsBus[NumArretBusAMontrer-1].y].RedessineCasesArretBus(indefinie);
end;
//---------------------------------------------------------------------------

procedure TfrmParamBus.ButtonOkClick(Sender: TObject);
begin
 if AppliqueChoix then ModalResult:=mrOk;
end;

procedure TfrmParamBus.ButtonAppliquerClick(Sender: TObject);
begin
 AppliqueChoix;
end;

procedure TfrmParamBus.SpinEditParametresChanged(Sender: TObject;
  NewValue: Integer);
begin
 if not InitialisationEnCours then ButtonAppliquer.Enabled:=true;
end;

procedure TfrmParamBus.CheckBoxClick(Sender: TObject);
begin
 if CheckBoxTout.Tag=0 then
  begin
   WindowState:=wsMinimized;
   frmSimulation.DrawGridSimul.Repaint;
  end;
end;

procedure TfrmParamBus.CheckBoxToutClick(Sender: TObject);
var i : Integer;
begin
 CheckBoxTout.Tag:=1;
 for i:=0 to NBMAXLIGNESBUS-1 do
  if cv.LignesBus[i].NbArrets>0 then
   (FindComponent('CheckBox'+IntToStr(i+1)) as TCheckBox).Checked:=CheckBoxTout.Checked
  else
   (FindComponent('CheckBox'+IntToStr(i+1)) as TCheckBox).Checked:=false;
 CheckBoxTout.Tag:=0;
 WindowState:=wsMinimized;
 frmSimulation.DrawGridSimul.Repaint;
end;

procedure TfrmParamBus.FormResize(Sender: TObject);
var h, w : Integer;
begin
h:=GroupBox3.Height+GroupBox3.Top+7;
w:=max( GroupBox3.Width+GroupBox3.Left+11,
        LabelNumerosArrets.Width+LabelNumerosArrets.Left+9);
if Height<>h then Height:=h;
if Width<>w then Width:=w; 
end;

end.

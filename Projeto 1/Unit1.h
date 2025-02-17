//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
class TrgReta : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TImage *Image1;
	TButton *Button1;
	TLabel *Label1;
	TLabel *Label2;
	TListBox *lbPoligonos;
	TListBox *lbPontos;
	TLabel *lbVp;
	TLabel *lbMundo;
	TGroupBox *GroupBox1;
	TLabel *Label7;
	TEdit *lbValor;
	TButton *btnLeft;
	TButton *btnRight;
	TButton *btnUp;
	TButton *btnDown;
	TLabel *Label3;
	TButton *btnIn;
	TButton *Button3;
	TLabel *Label4;
	TButton *Button2;
	TButton *Button4;
	TRadioGroup *rgRetas;
	TGroupBox *gpTransforma��es;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *Edit1;
	TEdit *Edit2;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *edit10;
	TLabel *Label10;
	TButton *Button5;
	TButton *Button6;
	TLabel *Label11;
	TEdit *Edit4;
	TEdit *Edit5;
	TLabel *Label12;
	TLabel *Label13;
	TButton *Button7;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TButton *Button8;
	TEdit *Edit6;
	TEdit *Edit7;
	TGroupBox *GroupBox2;
	TLabel *Label17;
	TLabel *Label18;
	TEdit *lbxc;
	TEdit *lbyc;
	TButton *Button9;
	TEdit *raio;
	TLabel *Label19;
	TButton *Button10;
	TGroupBox *GroupBox3;
	TButton *Button11;
	TButton *Button12;
	TButton *Button13;
	TGroupBox *GroupBox4;
	TButton *Button14;
	TGroupBox *GroupBox5;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TEdit *edxmax;
	TEdit *edxmin;
	TEdit *edymax;
	TEdit *edymin;
	TButton *Button15;
	TGroupBox *GroupBox6;
	TButton *Button16;
	TButton *Button17;
	TButton *Button18;
	TButton *Button19;
	TButton *Button20;
	TGroupBox *GroupBox7;
	TButton *Button21;
	TButton *Button22;
	TButton *Button23;
	TLabel *Label24;
	TEdit *Edit3;
	TLabel *Label25;
	TEdit *Edit8;
	TLabel *Label26;
	TEdit *Edit9;
	TEdit *Edit11;
	TLabel *Label27;
	TLabel *Label28;
	TEdit *Edit17;
	TLabel *Label29;
	TLabel *Label30;
	TButton *Button24;
	TLabel *Label31;
	TEdit *Edit13;
	TButton *Button25;
	TButton *Button26;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall lbPoligonosClick(TObject *Sender);
	void __fastcall btnLeftClick(TObject *Sender);
	void __fastcall btnRightClick(TObject *Sender);
	void __fastcall btnUpClick(TObject *Sender);
	void __fastcall btnDownClick(TObject *Sender);
	void __fastcall btnInClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall Button19Click(TObject *Sender);
	void __fastcall Button20Click(TObject *Sender);
	void __fastcall Button21Click(TObject *Sender);
	void __fastcall Button23Click(TObject *Sender);
	void __fastcall Button24Click(TObject *Sender);
	void __fastcall Button25Click(TObject *Sender);
	void __fastcall Button22Click(TObject *Sender);
	void __fastcall Button26Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TrgReta(TComponent* Owner);
	void  atualizaMundo(int tipo);
};
//---------------------------------------------------------------------------
extern PACKAGE TrgReta *rgReta;
//---------------------------------------------------------------------------
#endif

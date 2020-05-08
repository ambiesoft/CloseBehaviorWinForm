#pragma once


namespace CloseBehaviorWinForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	/// <summary>
	/// Summary for FormMain
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
	public:
		FormMain(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FormMain()
		{
			if (components)
			{
				delete components;
			}
			delete sw_;
		}
	private: System::Windows::Forms::TextBox^  txtLogFile;
	private: System::Windows::Forms::CheckBox^  chkPreventDefaultWM_ENDESSSION;
	private: System::Windows::Forms::RadioButton^  rbReturnsZero;
	private: System::Windows::Forms::RadioButton^  rbReturnsOne;

	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->txtLogFile = (gcnew System::Windows::Forms::TextBox());
			this->chkPreventDefaultWM_ENDESSSION = (gcnew System::Windows::Forms::CheckBox());
			this->rbReturnsZero = (gcnew System::Windows::Forms::RadioButton());
			this->rbReturnsOne = (gcnew System::Windows::Forms::RadioButton());
			this->SuspendLayout();
			// 
			// txtLogFile
			// 
			this->txtLogFile->Location = System::Drawing::Point(28, 41);
			this->txtLogFile->Name = L"txtLogFile";
			this->txtLogFile->Size = System::Drawing::Size(539, 20);
			this->txtLogFile->TabIndex = 0;
			// 
			// chkPreventDefaultWM_ENDESSSION
			// 
			this->chkPreventDefaultWM_ENDESSSION->AutoSize = true;
			this->chkPreventDefaultWM_ENDESSSION->Location = System::Drawing::Point(28, 67);
			this->chkPreventDefaultWM_ENDESSSION->Name = L"chkPreventDefaultWM_ENDESSSION";
			this->chkPreventDefaultWM_ENDESSSION->Size = System::Drawing::Size(199, 17);
			this->chkPreventDefaultWM_ENDESSSION->TabIndex = 2;
			this->chkPreventDefaultWM_ENDESSSION->Text = L"Prevent Default WM_ENDESSSION";
			this->chkPreventDefaultWM_ENDESSSION->UseVisualStyleBackColor = true;
			this->chkPreventDefaultWM_ENDESSSION->CheckedChanged += gcnew System::EventHandler(this, &FormMain::chkPreventDefaultWM_ENDESSSION_CheckedChanged);
			// 
			// rbReturnsZero
			// 
			this->rbReturnsZero->AutoSize = true;
			this->rbReturnsZero->Checked = true;
			this->rbReturnsZero->Location = System::Drawing::Point(64, 90);
			this->rbReturnsZero->Name = L"rbReturnsZero";
			this->rbReturnsZero->Size = System::Drawing::Size(66, 17);
			this->rbReturnsZero->TabIndex = 3;
			this->rbReturnsZero->TabStop = true;
			this->rbReturnsZero->Text = L"returns 0";
			this->rbReturnsZero->UseVisualStyleBackColor = true;
			// 
			// rbReturnsOne
			// 
			this->rbReturnsOne->AutoSize = true;
			this->rbReturnsOne->Location = System::Drawing::Point(64, 113);
			this->rbReturnsOne->Name = L"rbReturnsOne";
			this->rbReturnsOne->Size = System::Drawing::Size(66, 17);
			this->rbReturnsOne->TabIndex = 4;
			this->rbReturnsOne->Text = L"returns 1";
			this->rbReturnsOne->UseVisualStyleBackColor = true;
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(621, 283);
			this->Controls->Add(this->rbReturnsOne);
			this->Controls->Add(this->rbReturnsZero);
			this->Controls->Add(this->chkPreventDefaultWM_ENDESSSION);
			this->Controls->Add(this->txtLogFile);
			this->Name = L"FormMain";
			this->Text = L"FormMain";
			this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &FormMain::FormMain_FormClosed);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormMain::FormMain_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		StreamWriter^ sw_;
		property String^ NowString
		{
			String^ get()
			{
				return DateTime::Now.ToLongTimeString();
			}
		}
	protected:
		void WriteLog(String^ message)
		{
			sw_->Write(message);
			sw_->Write(" at ");
			sw_->WriteLine(NowString);
			sw_->Flush();
		}
		virtual void WndProc(Message% m) override
		{
			switch (m.Msg)
			{
			case WM_QUERYENDSESSION:
				WriteLog("WM_QUERYENDSESSION");
				if(chkPreventDefaultWM_ENDESSSION->Checked)
				{
					if(rbReturnsZero->Checked)
					{
						WriteLog("At WM_QUERYENDSESSION returns 0");
						m.Result = (IntPtr)0;
						return;
					}
					if(rbReturnsOne->Checked)
					{
						WriteLog("At WM_QUERYENDSESSION returns 1");
						m.Result = (IntPtr)1;
						return;
					}
				}
				break;
			case WM_ENDSESSION:
				WriteLog("WM_ENDESSSION at");
				break;
			}
			Form::WndProc(m);
		}
	private: System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e) {
				 UpdateDialog();
				 String^ logFile = Application::ExecutablePath + ".txt";
				 txtLogFile->Text = logFile;

				 sw_ = gcnew StreamWriter(logFile, true);
				 sw_->WriteLine();
				 WriteLog("Started");

			 }
	private: System::Void FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 WriteLog("FormMain_FormClosing at");
			 }
	private: System::Void FormMain_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				 sw_->WriteLine("FormMain_FormClosed at " + NowString);
			 }
			 void UpdateDialog()
			 {
				 rbReturnsZero->Enabled = chkPreventDefaultWM_ENDESSSION->Checked;
				 rbReturnsOne->Enabled = chkPreventDefaultWM_ENDESSSION->Checked;
			 }
	private: System::Void chkPreventDefaultWM_ENDESSSION_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
				 UpdateDialog();
			 }
};
}


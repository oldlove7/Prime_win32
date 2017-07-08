namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.comboSimple = new System.Windows.Forms.ComboBox();
            this.comboDropDown = new System.Windows.Forms.ComboBox();
            this.comboDropDownList = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(42, 35);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // comboSimple
            // 
            this.comboSimple.DropDownStyle = System.Windows.Forms.ComboBoxStyle.Simple;
            this.comboSimple.FormattingEnabled = true;
            this.comboSimple.Location = new System.Drawing.Point(22, 125);
            this.comboSimple.Name = "comboSimple";
            this.comboSimple.Size = new System.Drawing.Size(134, 150);
            this.comboSimple.TabIndex = 1;
            this.comboSimple.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // comboDropDown
            // 
            this.comboDropDown.FormattingEnabled = true;
            this.comboDropDown.Location = new System.Drawing.Point(205, 124);
            this.comboDropDown.Name = "comboDropDown";
            this.comboDropDown.Size = new System.Drawing.Size(121, 20);
            this.comboDropDown.TabIndex = 2;
            // 
            // comboDropDownList
            // 
            this.comboDropDownList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboDropDownList.FormattingEnabled = true;
            this.comboDropDownList.Location = new System.Drawing.Point(424, 123);
            this.comboDropDownList.Name = "comboDropDownList";
            this.comboDropDownList.Size = new System.Drawing.Size(121, 20);
            this.comboDropDownList.TabIndex = 3;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(571, 427);
            this.Controls.Add(this.comboDropDownList);
            this.Controls.Add(this.comboDropDown);
            this.Controls.Add(this.comboSimple);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "WinForm_Study";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ComboBox comboSimple;
        private System.Windows.Forms.ComboBox comboDropDown;
        private System.Windows.Forms.ComboBox comboDropDownList;
    }
}


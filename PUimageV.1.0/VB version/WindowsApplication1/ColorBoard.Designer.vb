<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class ColorBoard
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.ColorImage = New System.Windows.Forms.PictureBox()
        Me.Rbar = New System.Windows.Forms.TrackBar()
        Me.Gbar = New System.Windows.Forms.TrackBar()
        Me.Bbar = New System.Windows.Forms.TrackBar()
        Me.RText = New System.Windows.Forms.TextBox()
        Me.GText = New System.Windows.Forms.TextBox()
        Me.BText = New System.Windows.Forms.TextBox()
        Me.R = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.SaveFileDialog1 = New System.Windows.Forms.SaveFileDialog()
        Me.Button3 = New System.Windows.Forms.Button()
        CType(Me.ColorImage, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.Rbar, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.Gbar, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.Bbar, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'ColorImage
        '
        Me.ColorImage.Location = New System.Drawing.Point(13, 13)
        Me.ColorImage.Name = "ColorImage"
        Me.ColorImage.Size = New System.Drawing.Size(390, 253)
        Me.ColorImage.TabIndex = 0
        Me.ColorImage.TabStop = False
        '
        'Rbar
        '
        Me.Rbar.Location = New System.Drawing.Point(454, 27)
        Me.Rbar.Maximum = 50
        Me.Rbar.Minimum = -50
        Me.Rbar.Name = "Rbar"
        Me.Rbar.Size = New System.Drawing.Size(276, 45)
        Me.Rbar.TabIndex = 1
        '
        'Gbar
        '
        Me.Gbar.Location = New System.Drawing.Point(454, 88)
        Me.Gbar.Maximum = 50
        Me.Gbar.Minimum = -50
        Me.Gbar.Name = "Gbar"
        Me.Gbar.Size = New System.Drawing.Size(276, 45)
        Me.Gbar.TabIndex = 2
        '
        'Bbar
        '
        Me.Bbar.Location = New System.Drawing.Point(454, 139)
        Me.Bbar.Maximum = 50
        Me.Bbar.Minimum = -50
        Me.Bbar.Name = "Bbar"
        Me.Bbar.Size = New System.Drawing.Size(276, 45)
        Me.Bbar.TabIndex = 3
        '
        'RText
        '
        Me.RText.Location = New System.Drawing.Point(752, 27)
        Me.RText.Name = "RText"
        Me.RText.Size = New System.Drawing.Size(60, 20)
        Me.RText.TabIndex = 4
        '
        'GText
        '
        Me.GText.Location = New System.Drawing.Point(752, 88)
        Me.GText.Name = "GText"
        Me.GText.Size = New System.Drawing.Size(60, 20)
        Me.GText.TabIndex = 5
        '
        'BText
        '
        Me.BText.Location = New System.Drawing.Point(752, 139)
        Me.BText.Name = "BText"
        Me.BText.Size = New System.Drawing.Size(60, 20)
        Me.BText.TabIndex = 6
        '
        'R
        '
        Me.R.AutoSize = True
        Me.R.Location = New System.Drawing.Point(433, 30)
        Me.R.Name = "R"
        Me.R.Size = New System.Drawing.Size(15, 13)
        Me.R.TabIndex = 7
        Me.R.Text = "R"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(433, 91)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(15, 13)
        Me.Label1.TabIndex = 8
        Me.Label1.Text = "G"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(433, 139)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(14, 13)
        Me.Label2.TabIndex = 9
        Me.Label2.Text = "B"
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(611, 210)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(75, 23)
        Me.Button1.TabIndex = 11
        Me.Button1.Text = "save"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(737, 210)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(75, 23)
        Me.Button2.TabIndex = 12
        Me.Button2.Text = "exit"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'Button3
        '
        Me.Button3.Location = New System.Drawing.Point(485, 210)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(75, 23)
        Me.Button3.TabIndex = 13
        Me.Button3.Text = "Origin Image"
        Me.Button3.UseVisualStyleBackColor = True
        '
        'ColorBoard
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(867, 301)
        Me.Controls.Add(Me.Button3)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.R)
        Me.Controls.Add(Me.BText)
        Me.Controls.Add(Me.GText)
        Me.Controls.Add(Me.RText)
        Me.Controls.Add(Me.Bbar)
        Me.Controls.Add(Me.Gbar)
        Me.Controls.Add(Me.Rbar)
        Me.Controls.Add(Me.ColorImage)
        Me.Name = "ColorBoard"
        Me.Text = "ColorBoard"
        CType(Me.ColorImage, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.Rbar, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.Gbar, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.Bbar, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents ColorImage As PictureBox
    Friend WithEvents Rbar As TrackBar
    Friend WithEvents Gbar As TrackBar
    Friend WithEvents Bbar As TrackBar
    Friend WithEvents RText As TextBox
    Friend WithEvents GText As TextBox
    Friend WithEvents BText As TextBox
    Friend WithEvents R As Label
    Friend WithEvents Label1 As Label
    Friend WithEvents Label2 As Label
    Friend WithEvents Button1 As Button
    Friend WithEvents Button2 As Button
    Friend WithEvents SaveFileDialog1 As SaveFileDialog
    Friend WithEvents Button3 As Button
End Class

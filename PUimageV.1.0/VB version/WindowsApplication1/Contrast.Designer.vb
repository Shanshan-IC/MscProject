﻿<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Contrast
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
        Me.TrackBar1 = New System.Windows.Forms.TrackBar()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.ContrastImage = New System.Windows.Forms.PictureBox()
        Me.save = New System.Windows.Forms.Button()
        Me.SaveFileDialog1 = New System.Windows.Forms.SaveFileDialog()
        CType(Me.TrackBar1, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.ContrastImage, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'TrackBar1
        '
        Me.TrackBar1.Location = New System.Drawing.Point(367, 49)
        Me.TrackBar1.Maximum = 125
        Me.TrackBar1.Minimum = -255
        Me.TrackBar1.Name = "TrackBar1"
        Me.TrackBar1.Size = New System.Drawing.Size(415, 45)
        Me.TrackBar1.TabIndex = 0
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(378, 80)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(28, 13)
        Me.Label1.TabIndex = 1
        Me.Label1.Text = "-255"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(757, 81)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(25, 13)
        Me.Label2.TabIndex = 2
        Me.Label2.Text = "125"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(636, 80)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(13, 13)
        Me.Label3.TabIndex = 3
        Me.Label3.Text = "0"
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(409, 157)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(75, 23)
        Me.Button1.TabIndex = 4
        Me.Button1.Text = "OK"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(691, 157)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(75, 23)
        Me.Button2.TabIndex = 5
        Me.Button2.Text = "Cancel"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'ContrastImage
        '
        Me.ContrastImage.Location = New System.Drawing.Point(12, 24)
        Me.ContrastImage.Name = "ContrastImage"
        Me.ContrastImage.Size = New System.Drawing.Size(349, 206)
        Me.ContrastImage.TabIndex = 6
        Me.ContrastImage.TabStop = False
        '
        'save
        '
        Me.save.Location = New System.Drawing.Point(551, 157)
        Me.save.Name = "save"
        Me.save.Size = New System.Drawing.Size(75, 23)
        Me.save.TabIndex = 7
        Me.save.Text = "save"
        Me.save.UseVisualStyleBackColor = True
        '
        'Contrast
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(820, 268)
        Me.Controls.Add(Me.save)
        Me.Controls.Add(Me.ContrastImage)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.TrackBar1)
        Me.Name = "Contrast"
        Me.Text = "Contrast"
        CType(Me.TrackBar1, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.ContrastImage, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents TrackBar1 As TrackBar
    Friend WithEvents Label1 As Label
    Friend WithEvents Label2 As Label
    Friend WithEvents Label3 As Label
    Friend WithEvents Button1 As Button
    Friend WithEvents Button2 As Button
    Friend WithEvents ContrastImage As PictureBox
    Friend WithEvents save As Button
    Friend WithEvents SaveFileDialog1 As SaveFileDialog
End Class

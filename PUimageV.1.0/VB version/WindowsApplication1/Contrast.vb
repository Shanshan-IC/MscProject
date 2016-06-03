Public Class Contrast
    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.Close()
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.OK
        Dim val = TrackBar1.Value

        Dim bitclone As Bitmap = MainForm.bitmaps.Clone
        Dim r, g, b As Integer
        Dim pr As Integer

        MainForm.ProgressBar1.Value = 0
        MainForm.ProgressBar1.Maximum = MainForm.bitmaps.Height

        Dim lut(255) As Integer
        pr = TrackBar1.Value

        For i As Integer = 0 To 255
            lut(i) = (255 * (i - pr)) / (255 - (2 * pr))

            If lut(i) < 0 Then
                lut(i) = 0
            End If
            If lut(i) > 225 Then
                lut(i) = 225
            End If

        Next


        For y As Integer = 0 To bitclone.Height - 1
            For x As Integer = 0 To bitclone.Width - 1
                r = bitclone.GetPixel(x, y).R
                g = bitclone.GetPixel(x, y).G
                b = bitclone.GetPixel(x, y).B

                bitclone.SetPixel(x, y, Color.FromArgb(lut(r), lut(g), lut(b)))

            Next
            MainForm.ProgressBar1.Value = MainForm.ProgressBar1.Value + 1
        Next
        MainForm.PicImage.Image = bitclone
        MainForm.PicImage.Refresh()

        Me.Close()
    End Sub
End Class
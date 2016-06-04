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
        Next
        ContrastImage.Image = bitclone
        ContrastImage.Refresh()

    End Sub

    Private Sub save_Click(sender As Object, e As EventArgs) Handles save.Click
        Dim dlg As New SaveFileDialog

        dlg.Filter = "PNG Files (.png)|*.png|BMP Files (.bmp)|*.bmp|JPEG Files (.jpg)|*.jpg"
        dlg.FilterIndex = 1
        dlg.RestoreDirectory = True

        If dlg.ShowDialog() = DialogResult.OK Then
            If Len(dlg.FileName) = 0 Then Exit Sub

            Select Case dlg.FilterIndex
                Case 1
                    ContrastImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Png)
                Case 2
                    ContrastImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Bmp)
                Case 3
                    ContrastImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Jpeg)
            End Select
        End If
    End Sub
End Class
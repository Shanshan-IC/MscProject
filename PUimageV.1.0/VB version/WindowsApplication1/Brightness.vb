Public Class Brightness


    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.Close()
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Me.DialogResult = System.Windows.Forms.DialogResult.OK

        Dim mapclone As Bitmap = MainForm.bitmaps.Clone
        Dim r, g, b, j As Integer

        Dim hist(255) As Integer
        j = TrackBar1.Value

        For i As Integer = 0 To 255
            hist(i) = i + j

            If hist(i) > 225 Then
                hist(i) = 225
            End If
            If hist(i) < 0 Then
                hist(i) = 0
            End If
        Next

        For y As Integer = 0 To mapclone.Height - 1
            For x As Integer = 0 To mapclone.Width - 1
                r = mapclone.GetPixel(x, y).R
                g = mapclone.GetPixel(x, y).G
                b = mapclone.GetPixel(x, y).B

                mapclone.SetPixel(x, y, Color.FromArgb(hist(r), hist(g), hist(b)))
            Next
        Next
        brightImage.Image = mapclone
        brightImage.Refresh()
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        Dim dlg As New SaveFileDialog

        dlg.Filter = "PNG Files (.png)|*.png|BMP Files (.bmp)|*.bmp|JPEG Files (.jpg)|*.jpg"
        dlg.FilterIndex = 1
        dlg.RestoreDirectory = True

        If dlg.ShowDialog() = DialogResult.OK Then
            If Len(dlg.FileName) = 0 Then Exit Sub

            Select Case dlg.FilterIndex
                Case 1
                    brightImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Png)
                Case 2
                    brightImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Bmp)
                Case 3
                    brightImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Jpeg)
            End Select
        End If

    End Sub
End Class
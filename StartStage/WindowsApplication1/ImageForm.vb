Option Strict Off

Public Class ImageForm





    Public image As Bitmap      ' The image source
    Public filename As String   ' The file name of the image
    Private selectedPoint As Point = Nothing
    Public selectedArea As Rectangle

    Public Function ShowPicture(ByRef fileName As String) As Boolean
        If Not image Is Nothing Then
            image.Dispose()
        End If

        Me.filename = fileName

        selectedPoint = Nothing
        selectedArea = New Rectangle(0, 0, 0, 0)

        Me.Show()

        Try
            Dim file As Bitmap = New Bitmap(fileName)

            image = New Bitmap(file.Width, file.Height, Imaging.PixelFormat.Format24bppRgb)

            Dim g As Graphics = Graphics.FromImage(image)
            g.Clear(Color.White)
            g.DrawImage(file, 0, 0, file.Width, file.Height)

            ImageBox.SizeMode = PictureBoxSizeMode.StretchImage
            ImageBox.Width = image.Width
            ImageBox.Height = image.Height
            ImageBox.Image = CType(image, Image)

            Me.Width = ImageBox.Width + Me.Width - Me.ClientRectangle.Width
            Me.Height = ImageBox.Height + Me.Height - Me.ClientRectangle.Height

            Return True
        Catch e As Exception
            MessageBox.Show(e.Message, "Show Picture Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            Me.Close()

            Return False
        End Try
    End Function


    Private Sub ImageBox_Click(sender As Object, e As EventArgs) Handles ImageBox.Click

    End Sub
End Class
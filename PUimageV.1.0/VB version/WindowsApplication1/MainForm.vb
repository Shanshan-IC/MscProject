Public Class MainForm
    Inherits System.Windows.Forms.Form
    Public bitmaps As Bitmap
    Public originmap As Bitmap
    Public originwidth As Integer
    Public originheight As Integer


    Private Sub FileToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles FileToolStripMenuItem.Click

    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

    End Sub

    Sub bitmap_hist()

        Dim obraz As Bitmap = PicImage.Image
        Dim obraz1 As Bitmap = New Bitmap(obraz.Width, obraz.Height)
        Dim R, G, B As Integer

        For i As Integer = 0 To 255
            histR(i) = 0
            histG(i) = 0
            histB(i) = 0
        Next

        For x As Integer = 0 To PicImage.Image.Width - 1
            For y As Integer = 0 To PicImage.Image.Height - 1
                R = obraz.GetPixel(x, y).R
                G = obraz.GetPixel(x, y).G
                B = obraz.GetPixel(x, y).B
                histR(R) = histR(R) + 1
                histG(G) = histG(G) + 1
                histB(B) = histB(B) + 1
            Next
        Next

    End Sub

    Private Sub OpenAnImageToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles OpenAnImageToolStripMenuItem.Click

        Me.OpenFileDialog1.Filter = "Image Files (.bmp,.jpg,.png)|*.bmp;*.jpg;*.png"
        Me.OpenFileDialog1.FilterIndex = 1
        Me.OpenFileDialog1.RestoreDirectory = True

        If Me.OpenFileDialog1.ShowDialog = Windows.Forms.DialogResult.OK Then
            Dim FName As String = Me.OpenFileDialog1.FileName
            bitmaps = Image.FromFile(OpenFileDialog1.FileName)
            PicImage.Image = bitmaps
            PicImage.AutoSize = True
            originmap = PicImage.Image
            originwidth = originmap.Width
            originheight = originmap.Height


            bitmap_hist()
            Me.Refresh()

        End If

    End Sub

    Private Sub MenuStrip1_ItemClicked(sender As Object, e As ToolStripItemClickedEventArgs) Handles MenuStrip1.ItemClicked

    End Sub

    Private Sub PictureBox1_Click(sender As Object, e As EventArgs) Handles PicImage.Click

    End Sub

    Private Sub SaveToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SaveToolStripMenuItem.Click
        Dim dlg As New SaveFileDialog

        dlg.Filter = "PNG Files (.png)|*.png|BMP Files (.bmp)|*.bmp|JPEG Files (.jpg)|*.jpg"
        dlg.FilterIndex = 1
        dlg.RestoreDirectory = True

        If dlg.ShowDialog() = DialogResult.OK Then
            If Len(dlg.FileName) = 0 Then Exit Sub

            Select Case dlg.FilterIndex
                Case 1
                    PicImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Png)
                Case 2
                    PicImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Bmp)
                Case 3
                    PicImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Jpeg)
            End Select
        End If
    End Sub

    Private Sub ExitToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ExitToolStripMenuItem.Click
        Dim dialog As DialogResult
        dialog = MessageBox.Show("Do you want to save the image before exit?",
                                           "Exit", MessageBoxButtons.YesNoCancel)
        Select Case dialog
            Case Windows.Forms.DialogResult.Yes
                Me.OpenFileDialog1.Filter = "Image Files (.bmp,.jpg,.png)|*.bmp;*.jpg;*.png"
                Me.OpenFileDialog1.FilterIndex = 1
                Me.OpenFileDialog1.RestoreDirectory = True

                SaveImage.ShowDialog()

                If SaveImage.FileName > "" Then
                    PicImage.Image.Save(SaveImage.FileName)
                End If
                Me.Close()
            Case Windows.Forms.DialogResult.No
                Me.Close()
            Case Windows.Forms.DialogResult.Cancel

        End Select
    End Sub

    Private Sub UndoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles UndoToolStripMenuItem.Click

    End Sub

    Private Sub AboutPUIPToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AboutPUIPToolStripMenuItem.Click
        MsgBox("Pressure Ulcers Image Beta v 1.1 & Environment.NewLine" & "Recources could be gained from https: //github.com/Shanshan-IC/MscProject" & Environment.NewLine & Environment.NewLine & "Copyright © 2016 ShanshanFu", MsgBoxStyle.Information, "About")
    End Sub


    Private Sub PUIPHelpToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles PUIPHelpToolStripMenuItem.Click

    End Sub


    Private Sub ZoomToInToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ZoomToInToolStripMenuItem.Click
        Me.PicImage.Width += 20%
        Me.PicImage.Height += 20%

    End Sub

    Private Sub Zoom1Tool_Click(sender As Object, e As EventArgs)

    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs)

    End Sub

    Private Sub Zoom_Click(sender As Object, e As EventArgs)

    End Sub

    Private Sub ZoomToFitToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ZoomToFitToolStripMenuItem.Click
        Me.PicImage.Width = originwidth
        Me.PicImage.Height = originheight
    End Sub

    Private Sub ZoomToOutToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ZoomToOutToolStripMenuItem.Click
        Me.PicImage.Width -= 20%
        Me.PicImage.Height -= 20%
    End Sub

    Private Sub RightRotateToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles RightRotateToolStripMenuItem.Click

        Dim w As Integer = Me.PicImage.Width
        Dim h As Integer = Me.PicImage.Height

        Me.PicImage.Image.RotateFlip(RotateFlipType.Rotate90FlipNone)
        Me.PicImage.Height = h
        Me.PicImage.Width = w

        Me.PicImage.Refresh()
    End Sub

    Private Sub LeftRotateToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LeftRotateToolStripMenuItem.Click
        Dim w As Integer = Me.PicImage.Width
        Dim h As Integer = Me.PicImage.Height

        Me.PicImage.Image.RotateFlip(RotateFlipType.Rotate90FlipXY)
        Me.PicImage.Height = h
        Me.PicImage.Width = w
        Me.PicImage.Refresh()

    End Sub

    Private Sub GridToolStripMenuItem_Click(sender As Object, e As EventArgs)

    End Sub

    Private Sub AnalysisToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AnalysisToolStripMenuItem.Click

    End Sub

    Private Sub MeanFilterToolStripMenuItem_Click(sender As Object, e As EventArgs)

    End Sub

    Private Sub HistogramToolStripMenuItem_Click(sender As Object, e As EventArgs)

    End Sub

    Dim histR(255), histB(255), histG(255) As Integer

    Private Sub Panel3_Paint(sender As Object, e As PaintEventArgs) Handles Panel3.Paint
        If histR.Max <> 0 Then
            For x = 0 To 255
                Dim y1, y2 As Integer
                y1 = Panel1.Height - 1
                y2 = Panel1.Height - 1 - (histB(x) * Panel1.Height / histB.Max)
                e.Graphics.DrawLine(Pens.Blue, x, y1, x, y2)
            Next
        End If

    End Sub

    Private Sub BrightenssToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles BrightenssToolStripMenuItem.Click
        Dim bright = New Brightness
        bright.brightImage.Image = PicImage.Image
        bright.Show()
    End Sub

    Private Sub GrayShadeToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles GrayShadeToolStripMenuItem.Click
        Dim pomocniczyObraz2 As Bitmap = bitmaps.Clone
        Dim r, g, b, srednia As Integer
        ProgressBar1.Value = 0
        ProgressBar1.Maximum = bitmaps.Height
        For y As Integer = 0 To pomocniczyObraz2.Height - 1
            For x As Integer = 0 To pomocniczyObraz2.Width - 1
                r = pomocniczyObraz2.GetPixel(x, y).R
                g = pomocniczyObraz2.GetPixel(x, y).G
                b = pomocniczyObraz2.GetPixel(x, y).B
                srednia = (r + g + b) / 3
                r = srednia
                g = srednia
                b = srednia
                pomocniczyObraz2.SetPixel(x, y, Color.FromArgb(r, g, b))
            Next
            ProgressBar1.Value = ProgressBar1.Value + 1
        Next
        PicImage.Image = pomocniczyObraz2
        PicImage.Refresh()

        bitmap_hist()
        Me.Refresh()

    End Sub

    Private Sub HistogramBalanceToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles HistogramBalanceToolStripMenuItem.Click
        Dim pic As Bitmap = bitmaps.Clone
        Dim wartosc As Color
        Dim R, G, B As Integer
        Dim histR(255) As Integer
        Dim histG(255) As Integer
        Dim histB(255) As Integer
        Dim N As Integer

        Dim dystrR(255) As Integer
        Dim dystrG(255) As Integer
        Dim dystrB(255) As Integer

        Dim skalR(255) As Integer
        Dim skalG(255) As Integer
        Dim skalB(255) As Integer

        ProgressBar1.Value = 0
        ProgressBar1.Maximum = pic.Height * 1.5

        N = pic.Width * pic.Height

        For x As Integer = 0 To pic.Width - 1
            For y As Integer = 0 To pic.Height - 1
                wartosc = pic.GetPixel(x, y)
                R = wartosc.R
                G = wartosc.G
                B = wartosc.B
                histR(R) = histR(R) + 1
                histG(G) = histG(G) + 1
                histB(B) = histB(B) + 1
            Next
        Next


        dystrR(0) = histR(0)
        dystrG(0) = histG(0)
        dystrB(0) = histB(0)

        For i As Integer = 0 To 254
            dystrR(i + 1) = histR(i) + dystrR(i)
            If dystrR(i + 1) > N Then
                dystrR(i + 1) = N
            End If
            dystrG(i + 1) = histG(i) + dystrG(i)
            If dystrG(i + 1) > N Then
                dystrG(i + 1) = N
            End If
            dystrB(i + 1) = histB(i) + dystrB(i)
            If dystrB(i + 1) > N Then
                dystrB(i + 1) = N
            End If
        Next


        For i As Integer = 0 To 255
            skalR(i) = dystrR(i) * 255 / (pic.Width * pic.Height)
            skalG(i) = dystrG(i) * 255 / (pic.Width * pic.Height)
            skalB(i) = dystrB(i) * 255 / (pic.Width * pic.Height)
        Next
        For x As Integer = 0 To pic.Width - 1
            For y As Integer = 0 To pic.Height - 1
                wartosc = pic.GetPixel(x, y)
                R = wartosc.R
                G = wartosc.G
                B = wartosc.B
                R = skalR(R)
                G = skalG(G)
                B = skalB(B)
                wartosc = Color.FromArgb(R, G, B)
                pic.SetPixel(x, y, wartosc)
            Next
            ProgressBar1.Value = ProgressBar1.Value + 1

        Next
        PicImage.Image = pic
        PicImage.Refresh()

        bitmap_hist()
        Me.Refresh()
    End Sub

    Private Sub AverageFilterToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AverageFilterToolStripMenuItem.Click
        Dim pic1 As Bitmap = bitmaps.Clone
        Dim pic2 As Bitmap = bitmaps.Clone
        Dim wartosc As Color
        Dim tablicaR(pic1.Width, pic1.Height) As Long
        Dim tablicaG(pic1.Width, pic1.Height) As Long
        Dim tablicaB(pic1.Width - 1, pic1.Height - 1) As Long
        ProgressBar1.Value = 0
        ProgressBar1.Maximum = pic1.Height * 1.5

        For x As Integer = 0 To pic1.Width - 1
            For y As Integer = 0 To pic1.Height - 1

                If x > 0 And y > 0 And x < pic1.Width - 2 And y < pic1.Height - 2 Then

                    tablicaR(x, y) = (CLng(pic1.GetPixel(x - 1, y + 1).R) + CLng(pic1.GetPixel(x, y + 1).R) + CLng(pic1.GetPixel(x + 1, y + 1).R) + CLng(pic1.GetPixel(x - 1, y).R) + CLng(pic1.GetPixel(x, y).R) + CLng(pic1.GetPixel(x + 1, y).R) + CLng(pic1.GetPixel(x - 1, y - 1).R) + CLng(pic1.GetPixel(x, y - 1).R) + CLng(pic1.GetPixel(x + 1, y - 1).R)) / 9
                    tablicaG(x, y) = (CLng(pic1.GetPixel(x - 1, y + 1).G) + CLng(pic1.GetPixel(x, y + 1).G) + CLng(pic1.GetPixel(x + 1, y + 1).G) + CLng(pic1.GetPixel(x - 1, y).G) + CLng(pic1.GetPixel(x, y).G) + CLng(pic1.GetPixel(x + 1, y).G) + CLng(pic1.GetPixel(x - 1, y - 1).G) + CLng(pic1.GetPixel(x, y - 1).G) + CLng(pic1.GetPixel(x + 1, y - 1).G)) / 9
                    tablicaB(x, y) = (CLng(pic1.GetPixel(x - 1, y + 1).B) + CLng(pic1.GetPixel(x, y + 1).B) + CLng(pic1.GetPixel(x + 1, y + 1).B) + CLng(pic1.GetPixel(x - 1, y).B) + CLng(pic1.GetPixel(x, y).B) + CLng(pic1.GetPixel(x + 1, y).B) + CLng(pic1.GetPixel(x - 1, y - 1).B) + CLng(pic1.GetPixel(x, y - 1).B) + CLng(pic1.GetPixel(x + 1, y - 1).B)) / 9

                Else
                    tablicaR(x, y) = 0
                    tablicaG(x, y) = 0
                    tablicaB(x, y) = 0
                End If

                wartosc = Color.FromArgb(tablicaR(x, y), tablicaG(x, y), tablicaB(x, y))
                pic2.SetPixel(x, y, wartosc)

            Next
            ProgressBar1.Value = ProgressBar1.Value + 1
        Next
        PicImage.Image = pic2
        PicImage.Refresh()
        bitmap_hist()
        Me.Refresh()
    End Sub

    Private Sub CopyToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CopyToolStripMenuItem.Click
        'PictureBox2.Image = AxPictureClip1.Picture
    End Sub

    Private Sub SimpleSmoothingToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SimpleSmoothingToolStripMenuItem.Click
        Dim pic1 As Bitmap = bitmaps.Clone
        Dim blocksize As Short = 3
        ProgressBar1.Value = 0
        ProgressBar1.Maximum = pic1.Height * 1.5
        Dim r, g, b, rr, gg, bb As Integer
        r = 0 : g = 0 : b = 0
        For x As Integer = Int(blocksize / 2) To pic1.Width - Int(blocksize / 2) - 1
            For y As Integer = Int(blocksize / 2) To pic1.Height - Int(blocksize / 2) - 1
                For k1 = -Int(blocksize / 2) To Int(blocksize / 2)
                    For k2 = -Int(blocksize / 2) To Int(blocksize / 2)
                        r = r + pic1.GetPixel(x, y).R
                        g = g + pic1.GetPixel(x, y).G
                        b = b + pic1.GetPixel(x, y).B
                    Next

                Next
                rr = r / 9
                gg = g / 9
                bb = b / 9
                If rr < 0 Then rr = 0
                If rr > 255 Then rr = 255
                If gg < 0 Then gg = 0
                If gg > 255 Then gg = 255
                If bb < 0 Then bb = 0
                If bb > 255 Then bb = 255
            Next
            ProgressBar1.Value = ProgressBar1.Value + 1
        Next
        PicImage.Image = pic1
        PicImage.Refresh()

        bitmap_hist()
        Me.Refresh()

    End Sub

    Private Sub NeonToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NeonToolStripMenuItem.Click


        Dim n As Short = 0
        Dim pic1 As Bitmap = bitmaps.Clone
        Dim r, g, b, r2, g2, b2, r3, g3, b3, rr, gg, bb As Integer
        ProgressBar1.Value = 0
        ProgressBar1.Maximum = bitmaps.Width

        For x As Integer = 0 To pic1.Width - 2
            For y As Integer = 0 To pic1.Height - 2

                r = pic1.GetPixel(x, y).R
                g = pic1.GetPixel(x, y).G
                b = pic1.GetPixel(x, y).B

                r2 = pic1.GetPixel(x + 1, y).R
                g2 = pic1.GetPixel(x + 1, y).G
                b2 = pic1.GetPixel(x + 1, y).B

                r3 = pic1.GetPixel(x, y + 1).R
                g3 = pic1.GetPixel(x, y + 1).G
                b3 = pic1.GetPixel(x, y + 1).B

                rr = 2 * ((r - r2) ^ 2 + (r - r3) ^ 2) ^ 0.5
                gg = 2 * ((g - g2) ^ 2 + (g - g3) ^ 2) ^ 0.5
                bb = 2 * ((b - b2) ^ 2 + (b - b3) ^ 2) ^ 0.5

                If rr < 0 Then rr = 0
                If rr > 255 Then rr = 255
                If gg < 0 Then gg = 0
                If gg > 255 Then gg = 255
                If bb < 0 Then bb = 0
                If bb > 255 Then bb = 255
                pic1.SetPixel(x, y, Color.FromArgb(rr, gg, bb))

            Next
            ProgressBar1.Value = ProgressBar1.Value + 1
        Next
        PicImage.Image = pic1
        PicImage.Refresh()
        bitmap_hist()
        Me.Refresh()


    End Sub

    'no very distinct effect
    Private Sub SharpenToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SharpenToolStripMenuItem.Click
        Dim mapclone As Bitmap = bitmaps.Clone
        Dim r, g, b, r2, g2, b2, rr, gg, bb As Integer
        ProgressBar1.Value = 0
        ProgressBar1.Maximum = bitmaps.Height
        For y As Integer = 1 To mapclone.Height - 1
            For x As Integer = 1 To mapclone.Width - 1
                r = mapclone.GetPixel(x, y).R
                g = mapclone.GetPixel(x, y).G
                b = mapclone.GetPixel(x, y).B

                r2 = mapclone.GetPixel(x, y).R
                g2 = mapclone.GetPixel(x, y).G
                b2 = mapclone.GetPixel(x, y).B

                rr = r + Math.Abs((r - r2) * 3)
                gg = g + Math.Abs((g - g2) * 3)
                bb = b + Math.Abs((b - b2) * 3)

                If rr < 0 Then rr = 0
                If rr > 255 Then rr = 255
                If gg < 0 Then gg = 0
                If gg > 255 Then gg = 255
                If bb < 0 Then bb = 0
                If bb > 255 Then bb = 255

                mapclone.SetPixel(x, y, Color.FromArgb(rr, gg, bb))
            Next
            ProgressBar1.Value = ProgressBar1.Value + 1
        Next
        PicImage.Image = mapclone
        PicImage.Refresh()

        bitmap_hist()
        Me.Refresh()
    End Sub

    Private Sub EmbossToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles EmbossToolStripMenuItem.Click
        Dim emboss = New Emboss
        emboss.EmbossImage.Image = PicImage.Image
        emboss.Show()
    End Sub

    Private Sub MosaicToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles MosaicToolStripMenuItem.Click
        Dim mapclone As Bitmap = bitmaps.Clone
        Dim r, g, b, rr, gg, bb As Integer
        ProgressBar1.Value = 0
        ProgressBar1.Maximum = bitmaps.Width
        r = 0 : g = 0 : b = 0
        For y As Integer = 0 To mapclone.Height - 6 Step 5
            For x As Integer = 0 To mapclone.Width - 6 Step 5
                For k1 As Integer = 0 To 5
                    For k2 As Integer = 0 To 5
                        r = r + mapclone.GetPixel(x + k1, y + k2).R
                        g = g + mapclone.GetPixel(x + k1, y + k2).G
                        b = b + mapclone.GetPixel(x + k1, y + k2).B
                    Next
                Next
                rr = r / 25
                gg = g / 25
                bb = b / 25

                If rr < 0 Then rr = 0
                If rr > 255 Then rr = 255
                If gg < 0 Then gg = 0
                If gg > 255 Then gg = 255
                If bb < 0 Then bb = 0
                If bb > 255 Then bb = 255
                For k1 = 0 To 5
                    For k2 = 0 To 5
                        mapclone.SetPixel(x, y, Color.FromArgb(rr, gg, bb))
                    Next
                Next
            Next

            ProgressBar1.Value = ProgressBar1.Value + 1
        Next
        PicImage.Image = mapclone
        PicImage.Refresh()

        bitmap_hist()
        Me.Refresh()
    End Sub

    Private Sub ExposureUnbalancedToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ExposureUnbalancedToolStripMenuItem.Click

    End Sub

    Private Sub TwowayToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles TwowayToolStripMenuItem.Click

    End Sub

    Private Sub ToolStripButton1_Click(sender As Object, e As EventArgs) Handles ToolStripButton1.Click
        Me.OpenFileDialog1.Filter = "Image Files (.bmp,.jpg,.png)|*.bmp;*.jpg;*.png"
        Me.OpenFileDialog1.FilterIndex = 1
        Me.OpenFileDialog1.RestoreDirectory = True

        If Me.OpenFileDialog1.ShowDialog = Windows.Forms.DialogResult.OK Then
            Dim FName As String = Me.OpenFileDialog1.FileName
            bitmaps = Image.FromFile(OpenFileDialog1.FileName)
            PicImage.Image = bitmaps
            bitmap_hist()
            Me.Refresh()

        End If
    End Sub

    Private Sub ToolStripButton2_Click(sender As Object, e As EventArgs) Handles ToolStripButton2.Click
        Dim dlg As New SaveFileDialog

        dlg.Filter = "PNG Files (.png)|*.png|BMP Files (.bmp)|*.bmp|JPEG Files (.jpg)|*.jpg"
        dlg.FilterIndex = 1
        dlg.RestoreDirectory = True

        If dlg.ShowDialog() = DialogResult.OK Then
            If Len(dlg.FileName) = 0 Then Exit Sub

            Select Case dlg.FilterIndex
                Case 1
                    PicImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Png)
                Case 2
                    PicImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Bmp)
                Case 3
                    PicImage.Image.Save(dlg.FileName, Imaging.ImageFormat.Jpeg)
            End Select
        End If

    End Sub

    Private Sub ToolStripButton6_Click(sender As Object, e As EventArgs) Handles ToolStripButton6.Click
        Me.PicImage.Width -= 20%
        Me.PicImage.Height -= 20%
    End Sub

    Private Sub ResetToolStripMenuItem_Click(sender As Object, e As EventArgs)
        PicImage.Image = originmap
        bitmap_hist()
        Me.Refresh()
    End Sub

    Private Sub ToolStripButton7_Click_1(sender As Object, e As EventArgs) Handles ToolStripButton7.Click
        PicImage.Image = originmap
        bitmap_hist()
        Me.Refresh()
    End Sub

    Private Sub FitToScreenToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles FitToScreenToolStripMenuItem.Click

    End Sub

    Private Sub ToolStripButton5_Click(sender As Object, e As EventArgs) Handles ToolStripButton5.Click
        Me.PicImage.Width += 20%
        Me.PicImage.Height += 20%
    End Sub

    Private Sub ToolStripSplitButton1_ButtonClick(sender As Object, e As EventArgs)

    End Sub

    Private Sub ColorContrastToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ColorContrastToolStripMenuItem.Click
        Dim contrast = New Contrast
        contrast.ContrastImage.Image = PicImage.Image
        contrast.Show()
    End Sub

    Private Sub ContrastToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ContrastToolStripMenuItem.Click
        Dim p1R, p1G, p1B, p2R, p2G, p2B As Integer
        Dim R, G, B, p As Integer
        Dim pic As Bitmap = PicImage.Image
        Dim pic1 As Bitmap = New Bitmap(pic.Width, pic.Height)

        bitmap_hist()

        p = 0
        For i As Integer = 0 To 255
            If histR(i) > p Then
                p1R = i
                Exit For
            End If
        Next
        For i As Integer = 0 To 255
            If histR(i) > p Then
                p2R = i
            End If
        Next

        For i As Integer = 0 To 255
            If histG(i) > p Then
                p1G = i
                Exit For
            End If
        Next


        For i As Integer = 0 To 255
            If histG(i) > p Then
                p2G = i
            End If
        Next

        For i As Integer = 0 To 255
            If histB(i) > p Then
                p1B = i
            End If
            Exit For
        Next

        For i As Integer = 0 To 255
            If histB(i) > p Then
                p2B = i
            End If

        Next

        ProgressBar1.Value = 0
        ProgressBar1.Maximum = pic.Width
        For x As Integer = 0 To PicImage.Image.Width - 1
            For y As Integer = 0 To PicImage.Image.Height - 1
                R = pic.GetPixel(x, y).R
                G = pic.GetPixel(x, y).G
                B = pic.GetPixel(x, y).B

                R = ((R - p1R) * 255) / (p2R - p1R)
                G = ((G - p1G) * 255) / (p2G - p1G)
                B = ((B - p1B) * 255) / (p2B - p1B)
                If R < 0 Then R = 0
                If G < 0 Then G = 0
                If B < 0 Then B = 0

                If R > 255 Then R = 255
                If G > 255 Then G = 255
                If B > 255 Then B = 255

                pic1.SetPixel(x, y, Color.FromArgb(R, G, B))
            Next
            ProgressBar1.Value = ProgressBar1.Value + 1
        Next
        PicImage.Image = pic1
        PicImage.Refresh()

        bitmap_hist()
        Me.Refresh()
    End Sub

    Private Sub ColorToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ColorToolStripMenuItem.Click
        Dim pic1 As Bitmap = bitmaps.Clone
        Dim r, g, b As Integer
        Dim j As Integer

        ProgressBar1.Value = 0
        ProgressBar1.Maximum = bitmaps.Height

        Dim hist(255) As Integer

        For i As Integer = 0 To 255
            hist(i) = i + j

            If hist(i) > 225 Then
                hist(i) = 225
            End If
            If hist(i) < 0 Then
                hist(i) = 0
            End If
        Next

        For y As Integer = 0 To pic1.Height - 1
            For x As Integer = 0 To pic1.Width - 1
                r = pic1.GetPixel(x, y).R
                g = pic1.GetPixel(x, y).G
                b = pic1.GetPixel(x, y).B

                pic1.SetPixel(x, y, Color.FromArgb(hist(r), hist(g), hist(b)))
            Next
            ProgressBar1.Value = ProgressBar1.Value + 1
        Next
        PicImage.Image = pic1
        PicImage.Refresh()

        bitmap_hist()
        Me.Refresh()

    End Sub

    Private Sub InvertToToolStripMenuItem_Click(sender As Object, e As EventArgs)

    End Sub

    Private Sub NegativeToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NegativeToolStripMenuItem.Click
        Dim mapclone As Bitmap = bitmaps.Clone
        Dim r, g, b As Integer
        ProgressBar1.Value = 0
        ProgressBar1.Maximum = bitmaps.Height

        For y As Integer = 0 To mapclone.Height - 1
            For x As Integer = 0 To mapclone.Width - 1
                r = mapclone.GetPixel(x, y).R
                g = mapclone.GetPixel(x, y).G
                b = mapclone.GetPixel(x, y).B
                r = 255 - r
                g = 255 - g
                b = 255 - b
                mapclone.SetPixel(x, y, Color.FromArgb(r, g, b))

            Next
            ProgressBar1.Value = ProgressBar1.Value + 1
        Next
        PicImage.Image = mapclone
        PicImage.Refresh()
        bitmap_hist()
        Me.Refresh()
    End Sub

    Private Sub Panel2_Paint(sender As Object, e As PaintEventArgs) Handles Panel2.Paint
        If histR.Max <> 0 Then
            For x = 0 To 255
                Dim y1, y2 As Integer
                y1 = Panel1.Height - 1
                y2 = Panel1.Height - 1 - (histG(x) * Panel1.Height / histG.Max)
                e.Graphics.DrawLine(Pens.Green, x, y1, x, y2)
            Next
        End If
    End Sub

    Private Sub Panel1_Paint(sender As Object, e As PaintEventArgs) Handles Panel1.Paint
        If histR.Max <> 0 Then
            For x = 0 To 255
                Dim y1, y2 As Integer
                y1 = Panel1.Height - 1
                y2 = Panel1.Height - 1 - (histR(x) * Panel1.Height / histR.Max)
                e.Graphics.DrawLine(Pens.Red, x, y1, x, y2)
            Next
        End If
    End Sub
End Class

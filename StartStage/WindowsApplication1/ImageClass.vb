Public Class ImageClass
    Private mImageType As Integer  'image type   0：gray；1：color（RGB）
    Private mHist(255) As Long ' Gray Histogram Diagram
    Private mWidth As Long, mHeight As Long ' width and height of image
    Private mFwidth As Long ' memory bytes mFwidth = (mWidth+3)\4*4
    Private ImageB() As Byte ' store gray image data
    Private rHist(255) As Long ' Red Histogram
    Private bHist(255) As Long ' Blue Histogram
    Private gHist(255) As Long ' Green Histogram
    Private mPixels As Long, mSize As Long ' number of pixel and bytes
    Private v(255) As Single 'Frequency of Gray Histogram
    Private ImageC() As Byte ' Color image data
    Private Cpos() As Long ' The first row of color image
    Private isOpened As Boolean
    Private BMap As Bitmap ' Bitmap is VB.NET and C# basic image class
    Private xWmin As Double, yWmin As Double, xWmax As Double, yWmax As Double
    Private xWmin0 As Double, yWmin0 As Double, xWmax0 As Double, yWmax0 As Double
    Private mImageName As String
    Private CSize As Long ' Color image size
    Private mCWidth As Long ' color image memory bytes per row，mCWidth = (mWidth*3+3)\4*4
    Private CurrentEdit As SByte = -1 'the times that changed
    Private OldBMap(0) As Bitmap 'save the previous image
    Public Event ImageChanged()
    Public Event histchanged()

    'Gray Histogram Diagram'
    Public Sub hist(Optional ByRef text As String = Nothing)
        Dim i As Long, j As Integer, pos As Long
        If mImageType = 0 Then
            ' Dim n(255) As Integer 'n(i) is pixel number of gray i
            For i = 0 To 255
                mHist(i) = 0
            Next i
            For i = 0 To mHeight - 1
                For j = 0 To mWidth - 1
                    pos = mFwidth * i + j
                    mHist(ImageB(pos)) += 1
                Next j
            Next i
            For i = 0 To 255
                v(i) = mHist(i) / mPixels
            Next i
            '24 color image bgrbgr
            Dim max, min, h, avg, s As Double
            max = 0
            min = mPixels
            If text IsNot Nothing Then
                For i = 0 To 255
                    min = Math.Min(min, mHist(i))
                    max = Math.Max(max, mHist(i))
                    avg += i * mHist(i) / mPixels 'Mean gray
                    If mHist(i) <> 0 Then
                        h += -mHist(i) / mPixels * Math.Log(mHist(i) / mPixels) / Math.Log(2) '

                    End If
                Next
                For i = 0 To 255
                    s += mHist(i) * (i - avg) ^ 2 / mPixels 'standard deviation
                Next
                max = max / mPixels
                min = min / mPixels
                s = Math.Sqrt(s)
                text = "Max=" & Format(max, "0.00%") & Space(4) & "Min=" & Format(min, "0.00%") &
                Space(4) & "Entropy=" & Format(h, "0.00") & Space(4) & "Mean=" & Format(avg, "0.00") &
                Space(4) & "Deviation=" & Format(s, "0.00")
            End If
        ElseIf mImageType = 1 Then
            For i = 0 To 255
                mHist(i) = 0
                rHist(i) = 0
                gHist(i) = 0
                bHist(i) = 0
            Next
            For i = 0 To mPixels - 1
                Dim m As Byte
                pos = Cpos(i \ mWidth) + 3 * (i Mod mWidth)
                bHist(ImageC(pos)) += 1
                gHist(ImageC(pos + 1)) += 1
                rHist(ImageC(pos + 2)) += 1
                m = 0.299 * ImageC(pos + 2) + 0.587 * ImageC(pos + 1) + 0.114 * ImageC(pos)
                mHist(m) += 1
            Next
            Dim max, min As Double
            max = 0
            min = mPixels
            If text IsNot Nothing Then
                For i = 0 To 255
                    min = Math.Min(min, mHist(i))
                    min = Math.Min(min, rHist(i))
                    min = Math.Min(min, gHist(i))
                    min = Math.Min(min, bHist(i))
                    max = Math.Max(max, mHist(i))
                    max = Math.Max(max, rHist(i))
                    max = Math.Max(max, gHist(i))
                    max = Math.Max(max, bHist(i))
                Next
                min = min / mPixels
                max = max / mPixels
                text = "Max=" & Format(max, "0.00%") & Space(4) & "Min=" & Format(min, "0.00%")
            End If
        End If
    End Sub


    Public Function isEmpty() As Boolean
        Return isOpened
    End Function

    ' Load a image
    Public Function ReadImage(ByVal ImageName As String) As Integer
        If (Dir(ImageName) = "") Then     '
            Return 1
        End If
        If Not (BMap Is Nothing) Then
            BMap.Dispose()
        End If
        BMap = New Bitmap(ImageName)
        getBitMapData()
        xWmin = 0
        yWmin = 0
        xWmax = BMap.Width - 1
        yWmax = BMap.Height - 1
        mImageName = ImageName
        isOpened = True
    End Function

    Private Function getBitMapData(Optional ByVal Undo As Boolean = False) As Boolean
        ' 从BitMap对象里获取图像数据
        ' 在实际处理程序中一般不采用拷贝备份的做法，可以通过获得的数据指针，直接操作就可以了。
        ' 过程是：锁定内存，获取数据的起始地址，根据图像类型操作数据，结束锁定
        If BMap Is Nothing Then Return False ' 图像对象必须存在，完成实例化
        Dim i As Integer
        Dim rect As New Rectangle(0, 0, BMap.Width, BMap.Height) ' 设置锁定图像范围的矩形
        Dim bmpData As System.Drawing.Imaging.BitmapData = BMap.LockBits(rect,
            Drawing.Imaging.ImageLockMode.ReadOnly, BMap.PixelFormat) ' 锁定图像数据

        ' Get the address of the first line.
        Dim ptr As IntPtr = bmpData.Scan0 ' 获得图像数据的起始地址

        If BMap.PixelFormat = Imaging.PixelFormat.Format8bppIndexed Then
            ' 如果图像是8位索引图像，256彩色，256灰度图像
            mWidth = BMap.Width     '获得图像宽度
            mHeight = BMap.Height   '获得图像高度
            mFwidth = ((mWidth + 3) \ 4) * 4 '由于图像数据是每行的记录字节数为4的整倍数，估作此调整计算
            ' mWidth + 3 > mFwidth >= mWidth
            mSize = mFwidth * mHeight  ' 图像数据的大小
            mPixels = mWidth * mHeight ' 图像总像素个数
            ReDim ImageB(mSize - 1) ' 定义一个一维数组，保存图像数据，用于图像数据操作
            System.Runtime.InteropServices.Marshal.Copy(ptr, ImageB, 0, mSize) ' 拷贝数据
            mImageType = 0
        ElseIf BMap.PixelFormat = Imaging.PixelFormat.Format24bppRgb Then
            mWidth = BMap.Width
            mHeight = BMap.Height
            mCWidth = ((mWidth * 3 + 3) \ 4) * 4
            CSize = mCWidth * mHeight
            mPixels = mWidth * mHeight
            ReDim ImageC(CSize - 1)
            ' Copy the RGB values into the array.
            System.Runtime.InteropServices.Marshal.Copy(ptr, ImageC, 0, CSize)
            mImageType = 1
            ReDim Cpos(mHeight - 1)  ' Cpos数组纪录每行在ImageC中的起始位置
            For i = 0 To mHeight - 1
                Cpos(i) = i * mCWidth
            Next i
        End If
        hist()
        BMap.UnlockBits(bmpData) ' 解锁锁定的位图数据
        If Undo = False Then
            CurrentEdit = CurrentEdit + 1
            ReDim Preserve OldBMap(CurrentEdit)
            OldBMap(CurrentEdit) = BMap.Clone()
        End If
        RaiseEvent ImageChanged()
        RaiseEvent histchanged()
        Return True
    End Function
    Private Function co(ByVal pt As PointF, ByVal rect As Rectangle, ByVal ymax As Single)
        '将（i,v（i））转化为picturebox中的（x,y）,rect为图框
        Dim x As Single, y As Single
        x = pt.X * rect.Width / 255 + rect.X
        y = -pt.Y * rect.Height / ymax + rect.Height + rect.Y
        Return New PointF(x, y)
    End Function

    Public Sub drawhist(ByRef e As Graphics, ByVal rect As Rectangle)
        Dim max As Single, pts(255) As PointF, i As Short
        e.Clear(Color.White)
        If mImageType = 0 Then
            For i = 0 To 255
                If max < v(i) Then max = v(i)
            Next
            e.DrawLine(Pens.Black, co(New Point(0, 0), rect, max), co(New Point(255, 0), rect, max))
            e.DrawLine(Pens.Black, co(New Point(0, 0), rect, max), co(New PointF(0, max), rect, max))
            For i = 0 To 255
                pts(i) = co(New PointF(i, v(i)), rect, max)
            Next
            e.DrawLines(Pens.Black, pts)
        ElseIf mImageType = 1 Then
            max = 0
            For i = 0 To 255
                max = Math.Max(rHist(i), max)
                max = Math.Max(gHist(i), max)
                max = Math.Max(bHist(i), max)
                max = Math.Max(mHist(i), max)
            Next

            For i = 0 To 255
                pts(i) = co(New PointF(i, rHist(i)), rect, max)
            Next
            e.DrawLines(Pens.Red, pts)
            For i = 0 To 255
                pts(i) = co(New PointF(i, gHist(i)), rect, max)
            Next
            e.DrawLines(Pens.Green, pts)
            For i = 0 To 255
                pts(i) = co(New PointF(i, bHist(i)), rect, max)
            Next
            e.DrawLines(Pens.Blue, pts)
            For i = 0 To 255
                pts(i) = co(New PointF(i, mHist(i)), rect, max)
            Next
            e.DrawLines(Pens.Black, pts)
            e.DrawLine(Pens.Black, co(New Point(0, 0), rect, max), co(New Point(255, 0), rect, max))
            e.DrawLine(Pens.Black, co(New Point(0, 0), rect, max), co(New PointF(0, max), rect, max))
        End If
    End Sub

End Class

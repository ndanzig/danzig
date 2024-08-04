<Canvas
   xmlns="http://schemas.microsoft.com/client/2007"
   xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml">
    <TextBlock FontSize="12" Canvas.Left="<?php echo $_GET["cleft"]; ?>" Canvas.Top="<?php echo $_GET["ctop"]; ?>" Foreground="Black" Text="<?php echo $_GET["text"]; ?>">
        <TextBlock.RenderTransform>
          <TransformGroup>
                <RotateTransform Angle="<?php echo $_GET["angle"]; ?>"/>
          </TransformGroup>
        </TextBlock.RenderTransform>
    </TextBlock>
</Canvas>

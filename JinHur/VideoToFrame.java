package ourRocksProject;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import org.bytedeco.javacv.FFmpegFrameGrabber;
import org.bytedeco.javacv.Frame;
import org.bytedeco.javacv.Java2DFrameConverter;
public class test {
    public static void main(String []args) throws IOException, Exception
    {
        File myObj= new File("xxx.mp4");
        FFmpegFrameGrabber frameGrabber= new FFmpegFrameGrabber(myObj.getAbsoluteFile());
        frameGrabber.start();
        Frame f;
        BufferedImage bi;
        try {
            Java2DFrameConverter c= new Java2DFrameConverter();
            
            int num = 0;
            while(true) {
            	f= frameGrabber.grab();
            	if(f == null)
            		break;
            	
            	bi= c.convert(f);
            	
            	String file_name = "xxx" + num + ".png";
            	ImageIO.write(bi,"png", new File("C:\\Users\\32174937\\Desktop\\video\\img\\" + file_name));
            	num++;
            }
            
            frameGrabber.stop();
        } catch (Exception e) {
            //TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}


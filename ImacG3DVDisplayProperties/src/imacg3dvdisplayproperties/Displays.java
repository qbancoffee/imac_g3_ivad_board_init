/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package imacg3dvdisplayproperties;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import java.awt.Color;
import java.awt.Image;
import java.awt.Transparency;
import java.io.PrintStream;
import java.net.URL;
import java.util.Enumeration;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.prefs.Preferences;
import javax.swing.BorderFactory;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

/**
 *
 * @author Rocky Hill
 */
public class Displays extends javax.swing.JFrame {

    /**
     * Creates new form Displays
     */
    //define ImageIcons  
    private ImageIcon monitorImage;
    private ImageIcon rectangleImage;
    private ImageIcon positionImageMoveRight;
    private ImageIcon positionImageMoveLeft;
    private ImageIcon positionImageMoveUp;
    private ImageIcon positionImageMoveDown;
    private ImageIcon heightImageIncreaseHeight;
    private ImageIcon heightImageReduceHeight;
    private ImageIcon WidthImageIncreaseWidth;
    private ImageIcon WidthImageReduceWidth;
    private ImageIcon pincushionImageStretch;
    private ImageIcon pincushionImagePinch;
    private ImageIcon rotateImageClockwise;
    private ImageIcon rotateImageCounterClockwise;
    private ImageIcon keystoneImageStretchTop;
    private ImageIcon keystoneImagePinchTop;
    private ImageIcon parallelogramImageTiltRight;
    private ImageIcon parallelogramImageTiltLeft;

    //serial port stuff
    private Preferences prefs;
    private SerialPort port = null;
    private CommPortIdentifier portId = null;
    private String serialPortName;

    //random stuff
    private String OS = System.getProperty("os.name").toLowerCase();
    //temp stuff
    private Icon tmpIcon;
    private Thread sendSerial;
    private SerialTrigger st;


    public Displays() {

        try {
            // Set System L&F
            UIManager.setLookAndFeel(
                    UIManager.getSystemLookAndFeelClassName());
        } catch (UnsupportedLookAndFeelException e) {
            e.printStackTrace();
            // handle exception
        } catch (ClassNotFoundException e) {
            // handle exception
            e.printStackTrace();
        } catch (InstantiationException e) {
            // handle exception
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            // handle exception
            e.printStackTrace();
        }

        initComponents();
        // add radio buttons to group to make sure only one is 
        // selected at time.
        buttonGroupGeometry.add(jRadioButtonHeightWidth);
        buttonGroupGeometry.add(jRadioButtonKeystone);
        buttonGroupGeometry.add(jRadioButtonParallelogram);
        buttonGroupGeometry.add(jRadioButtonPincushion);
        buttonGroupGeometry.add(jRadioButtonPosition);
        buttonGroupGeometry.add(jRadioButtonRotate);
        buttonGroupGeometry.setSelected(jRadioButtonPosition.getModel(), true);

        //create ImageIcons from images  
        monitorImage = new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/monitor.png"));
        rectangleImage = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/rectangle.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        positionImageMoveRight = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/move_right.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        positionImageMoveLeft = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/move_left.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        positionImageMoveUp = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/move_up.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        positionImageMoveDown = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/move_down.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        heightImageIncreaseHeight = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/increase_height.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        heightImageReduceHeight = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/reduce_height.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        WidthImageIncreaseWidth = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/increase_width.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        WidthImageReduceWidth = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/reduce_width.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        pincushionImageStretch = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/pincushion_stretch.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        pincushionImagePinch = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/pincushion_pinch.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        rotateImageClockwise = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/rotate_clockwise.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        rotateImageCounterClockwise = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/rotate_counter_clockwise.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        keystoneImageStretchTop = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/keystone_stretch_top.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        keystoneImagePinchTop = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/keystone_pinch_top.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        parallelogramImageTiltRight = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/tilt_right.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));
        parallelogramImageTiltLeft = new ImageIcon(new ImageIcon(getClass().getResource("/imacg3dvdisplayproperties/resources/tilt_left.png")).getImage().getScaledInstance(48, 32, Image.SCALE_SMOOTH));

        //set monitor image
        jLabelMonitorImage.setIcon(monitorImage);
        
        
        selectRadioButtons();
        
        
        //enumerate serial ports
        String sp = "/dev/ttyUSB0";
        String spTmp = "";
        prefs = Preferences.userNodeForPackage(getClass());
        if (OS.indexOf("win") >= 0) {
            sp = "COM1";
        }//end if
        serialPortName = prefs.get("serialPortName", sp);

        CommPortIdentifier pid;
        Enumeration portIdentifiers = CommPortIdentifier.getPortIdentifiers();
        while (portIdentifiers.hasMoreElements()) {
            //Thread.sleep(100);

            pid = (CommPortIdentifier) portIdentifiers.nextElement();
            spTmp = new String(pid.getName());
            if (!spTmp.toLowerCase().contains("lpt")) {
                jComboBoxSerialPort.addItem(spTmp);
            }
            jComboBoxSerialPort.setSelectedItem(serialPortName);

        }// end while          

        pack();
        setLocationRelativeTo(null);

        setVisible(true);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        buttonGroupGeometry = new javax.swing.ButtonGroup();
        jTabbedPaneDisplay = new javax.swing.JTabbedPane();
        jPanelGeometry = new javax.swing.JPanel();
        jPanelSettings = new javax.swing.JPanel();
        jRadioButtonPosition = new javax.swing.JRadioButton();
        jRadioButtonHeightWidth = new javax.swing.JRadioButton();
        jRadioButtonPincushion = new javax.swing.JRadioButton();
        jRadioButtonRotate = new javax.swing.JRadioButton();
        jRadioButtonKeystone = new javax.swing.JRadioButton();
        jRadioButtonParallelogram = new javax.swing.JRadioButton();
        jLabelMonitorImage = new javax.swing.JLabel();
        jButtonRightTop = new javax.swing.JButton();
        jButtonRightBottom = new javax.swing.JButton();
        jButtonBottomLeft = new javax.swing.JButton();
        jButtonBottomRight = new javax.swing.JButton();
        jButtonFactoryDefaults = new javax.swing.JButton();
        jPanelColor = new javax.swing.JPanel();
        jPanelSerial = new javax.swing.JPanel();
        jComboBoxSerialPort = new javax.swing.JComboBox<>();
        jLabel1 = new javax.swing.JLabel();
        jButtonSerialConnect = new javax.swing.JButton();
        jButtonSerialDisconnect = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        jPanelSettings.setBorder(javax.swing.BorderFactory.createTitledBorder("Settings"));

        jRadioButtonPosition.setText("Position");
        jRadioButtonPosition.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jRadioButtonPositionActionPerformed(evt);
            }
        });

        jRadioButtonHeightWidth.setText("Height/Width");
        jRadioButtonHeightWidth.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jRadioButtonHeightWidthActionPerformed(evt);
            }
        });

        jRadioButtonPincushion.setText("Pincushion");
        jRadioButtonPincushion.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jRadioButtonPincushionActionPerformed(evt);
            }
        });

        jRadioButtonRotate.setText("Rotate");
        jRadioButtonRotate.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jRadioButtonRotateActionPerformed(evt);
            }
        });

        jRadioButtonKeystone.setText("Keystone");
        jRadioButtonKeystone.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jRadioButtonKeystoneActionPerformed(evt);
            }
        });

        jRadioButtonParallelogram.setText("Parallelogram");
        jRadioButtonParallelogram.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jRadioButtonParallelogramActionPerformed(evt);
            }
        });

        jButtonRightTop.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                jButtonRightTopMousePressed(evt);
            }
            public void mouseReleased(java.awt.event.MouseEvent evt) {
                jButtonRightTopMouseReleased(evt);
            }
        });
        jButtonRightTop.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonRightTopActionPerformed(evt);
            }
        });

        jButtonRightBottom.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                jButtonRightBottomMousePressed(evt);
            }
            public void mouseReleased(java.awt.event.MouseEvent evt) {
                jButtonRightBottomMouseReleased(evt);
            }
        });

        jButtonBottomLeft.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                jButtonBottomLeftMousePressed(evt);
            }
            public void mouseReleased(java.awt.event.MouseEvent evt) {
                jButtonBottomLeftMouseReleased(evt);
            }
        });

        jButtonBottomRight.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                jButtonBottomRightMousePressed(evt);
            }
            public void mouseReleased(java.awt.event.MouseEvent evt) {
                jButtonBottomRightMouseReleased(evt);
            }
        });

        javax.swing.GroupLayout jPanelSettingsLayout = new javax.swing.GroupLayout(jPanelSettings);
        jPanelSettings.setLayout(jPanelSettingsLayout);
        jPanelSettingsLayout.setHorizontalGroup(
            jPanelSettingsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelSettingsLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanelSettingsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanelSettingsLayout.createSequentialGroup()
                        .addComponent(jRadioButtonPosition)
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanelSettingsLayout.createSequentialGroup()
                        .addGroup(jPanelSettingsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addGroup(jPanelSettingsLayout.createSequentialGroup()
                                .addComponent(jRadioButtonParallelogram)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                            .addGroup(jPanelSettingsLayout.createSequentialGroup()
                                .addGroup(jPanelSettingsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(jRadioButtonHeightWidth)
                                    .addComponent(jRadioButtonPincushion)
                                    .addComponent(jRadioButtonRotate)
                                    .addComponent(jRadioButtonKeystone))
                                .addGap(0, 0, Short.MAX_VALUE)))
                        .addGap(79, 79, 79)
                        .addGroup(jPanelSettingsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addGroup(jPanelSettingsLayout.createSequentialGroup()
                                .addComponent(jButtonBottomLeft, javax.swing.GroupLayout.PREFERRED_SIZE, 48, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(106, 106, 106)
                                .addComponent(jButtonBottomRight, javax.swing.GroupLayout.PREFERRED_SIZE, 48, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(20, 20, 20))
                            .addComponent(jLabelMonitorImage, javax.swing.GroupLayout.PREFERRED_SIZE, 222, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(jPanelSettingsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jButtonRightBottom, javax.swing.GroupLayout.PREFERRED_SIZE, 48, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jButtonRightTop, javax.swing.GroupLayout.PREFERRED_SIZE, 48, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(140, 140, 140))))
        );

        jPanelSettingsLayout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {jButtonRightBottom, jButtonRightTop});

        jPanelSettingsLayout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {jButtonBottomLeft, jButtonBottomRight});

        jPanelSettingsLayout.setVerticalGroup(
            jPanelSettingsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelSettingsLayout.createSequentialGroup()
                .addGroup(jPanelSettingsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanelSettingsLayout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(jRadioButtonPosition)
                        .addGap(18, 18, 18)
                        .addGroup(jPanelSettingsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanelSettingsLayout.createSequentialGroup()
                                .addComponent(jRadioButtonHeightWidth)
                                .addGap(12, 12, 12)
                                .addComponent(jRadioButtonPincushion)
                                .addGap(18, 18, 18)
                                .addComponent(jRadioButtonRotate)
                                .addGap(18, 18, 18)
                                .addComponent(jRadioButtonKeystone))
                            .addComponent(jLabelMonitorImage, javax.swing.GroupLayout.PREFERRED_SIZE, 143, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addGroup(jPanelSettingsLayout.createSequentialGroup()
                                .addGap(9, 9, 9)
                                .addComponent(jButtonRightTop, javax.swing.GroupLayout.PREFERRED_SIZE, 32, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(59, 59, 59)
                                .addComponent(jButtonRightBottom, javax.swing.GroupLayout.PREFERRED_SIZE, 32, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addGroup(jPanelSettingsLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jButtonBottomLeft, javax.swing.GroupLayout.PREFERRED_SIZE, 32, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jButtonBottomRight, javax.swing.GroupLayout.PREFERRED_SIZE, 32, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addGroup(jPanelSettingsLayout.createSequentialGroup()
                        .addGap(210, 210, 210)
                        .addComponent(jRadioButtonParallelogram)))
                .addGap(62, 62, 62))
        );

        jPanelSettingsLayout.linkSize(javax.swing.SwingConstants.VERTICAL, new java.awt.Component[] {jButtonRightBottom, jButtonRightTop});

        jPanelSettingsLayout.linkSize(javax.swing.SwingConstants.VERTICAL, new java.awt.Component[] {jButtonBottomLeft, jButtonBottomRight});

        jButtonFactoryDefaults.setText("Factory Defaults");
        jButtonFactoryDefaults.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonFactoryDefaultsActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanelGeometryLayout = new javax.swing.GroupLayout(jPanelGeometry);
        jPanelGeometry.setLayout(jPanelGeometryLayout);
        jPanelGeometryLayout.setHorizontalGroup(
            jPanelGeometryLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelGeometryLayout.createSequentialGroup()
                .addGap(91, 91, 91)
                .addGroup(jPanelGeometryLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(jButtonFactoryDefaults, javax.swing.GroupLayout.PREFERRED_SIZE, 171, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jPanelSettings, javax.swing.GroupLayout.PREFERRED_SIZE, 550, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(92, Short.MAX_VALUE))
        );
        jPanelGeometryLayout.setVerticalGroup(
            jPanelGeometryLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelGeometryLayout.createSequentialGroup()
                .addGap(43, 43, 43)
                .addComponent(jPanelSettings, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 18, Short.MAX_VALUE)
                .addComponent(jButtonFactoryDefaults)
                .addContainerGap())
        );

        jTabbedPaneDisplay.addTab("Geometry", jPanelGeometry);

        javax.swing.GroupLayout jPanelColorLayout = new javax.swing.GroupLayout(jPanelColor);
        jPanelColor.setLayout(jPanelColorLayout);
        jPanelColorLayout.setHorizontalGroup(
            jPanelColorLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 733, Short.MAX_VALUE)
        );
        jPanelColorLayout.setVerticalGroup(
            jPanelColorLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 437, Short.MAX_VALUE)
        );

        jTabbedPaneDisplay.addTab("Color", jPanelColor);

        jLabel1.setText("Serial Port");

        jButtonSerialConnect.setText("Connect");
        jButtonSerialConnect.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonSerialConnectActionPerformed(evt);
            }
        });

        jButtonSerialDisconnect.setText("Disconnect");
        jButtonSerialDisconnect.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButtonSerialDisconnectActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanelSerialLayout = new javax.swing.GroupLayout(jPanelSerial);
        jPanelSerial.setLayout(jPanelSerialLayout);
        jPanelSerialLayout.setHorizontalGroup(
            jPanelSerialLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelSerialLayout.createSequentialGroup()
                .addGap(131, 131, 131)
                .addComponent(jLabel1)
                .addGap(18, 18, 18)
                .addGroup(jPanelSerialLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                    .addGroup(jPanelSerialLayout.createSequentialGroup()
                        .addComponent(jButtonSerialDisconnect)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(jButtonSerialConnect))
                    .addComponent(jComboBoxSerialPort, javax.swing.GroupLayout.PREFERRED_SIZE, 237, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(276, Short.MAX_VALUE))
        );

        jPanelSerialLayout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {jButtonSerialConnect, jButtonSerialDisconnect});

        jPanelSerialLayout.setVerticalGroup(
            jPanelSerialLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanelSerialLayout.createSequentialGroup()
                .addGap(60, 60, 60)
                .addGroup(jPanelSerialLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jComboBoxSerialPort, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel1))
                .addGap(50, 50, 50)
                .addGroup(jPanelSerialLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jButtonSerialConnect)
                    .addComponent(jButtonSerialDisconnect))
                .addContainerGap(255, Short.MAX_VALUE))
        );

        jPanelSerialLayout.linkSize(javax.swing.SwingConstants.VERTICAL, new java.awt.Component[] {jButtonSerialConnect, jButtonSerialDisconnect});

        jTabbedPaneDisplay.addTab("Serial", jPanelSerial);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jTabbedPaneDisplay, javax.swing.GroupLayout.PREFERRED_SIZE, 737, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jTabbedPaneDisplay, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(27, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jRadioButtonPositionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jRadioButtonPositionActionPerformed

        buttonGroupGeometry.setSelected(jRadioButtonPosition.getModel(), true);
        selectRadioButtons();        
    }//GEN-LAST:event_jRadioButtonPositionActionPerformed

    private void jRadioButtonHeightWidthActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jRadioButtonHeightWidthActionPerformed
        buttonGroupGeometry.setSelected(jRadioButtonHeightWidth.getModel(), true);
        selectRadioButtons(); 
    }//GEN-LAST:event_jRadioButtonHeightWidthActionPerformed

    private void jRadioButtonPincushionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jRadioButtonPincushionActionPerformed
        buttonGroupGeometry.setSelected(jRadioButtonPincushion.getModel(), true);
        selectRadioButtons(); 
    }//GEN-LAST:event_jRadioButtonPincushionActionPerformed

    private void jRadioButtonRotateActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jRadioButtonRotateActionPerformed
        buttonGroupGeometry.setSelected(jRadioButtonRotate.getModel(), true);
        selectRadioButtons(); 
    }//GEN-LAST:event_jRadioButtonRotateActionPerformed

    private void jRadioButtonKeystoneActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jRadioButtonKeystoneActionPerformed
        buttonGroupGeometry.setSelected(jRadioButtonKeystone.getModel(), true);
        selectRadioButtons(); 
    }//GEN-LAST:event_jRadioButtonKeystoneActionPerformed

    private void jRadioButtonParallelogramActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jRadioButtonParallelogramActionPerformed
        buttonGroupGeometry.setSelected(jRadioButtonParallelogram.getModel(), true);
        selectRadioButtons(); 
    }//GEN-LAST:event_jRadioButtonParallelogramActionPerformed

    private void jButtonRightTopActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonRightTopActionPerformed
     
    }//GEN-LAST:event_jButtonRightTopActionPerformed

    private void jButtonRightTopMousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jButtonRightTopMousePressed
        
        changeJButtonIcon(jButtonRightTop);
        sendCommand(0);
       
    }//GEN-LAST:event_jButtonRightTopMousePressed

    private void jButtonRightTopMouseReleased(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jButtonRightTopMouseReleased
        jButtonRightTop.setIcon(tmpIcon);
        stopThread();
    }//GEN-LAST:event_jButtonRightTopMouseReleased

    private void jButtonRightBottomMousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jButtonRightBottomMousePressed
      changeJButtonIcon(jButtonRightBottom);
      sendCommand(1);
    }//GEN-LAST:event_jButtonRightBottomMousePressed

    private void jButtonRightBottomMouseReleased(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jButtonRightBottomMouseReleased
        restoreJButtonIcon(jButtonRightBottom);
        stopThread();
    }//GEN-LAST:event_jButtonRightBottomMouseReleased

    private void jButtonBottomLeftMousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jButtonBottomLeftMousePressed
        changeJButtonIcon(jButtonBottomLeft);
        sendCommand(3);
    }//GEN-LAST:event_jButtonBottomLeftMousePressed

    private void jButtonBottomLeftMouseReleased(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jButtonBottomLeftMouseReleased
       restoreJButtonIcon(jButtonBottomLeft);
       stopThread();
    }//GEN-LAST:event_jButtonBottomLeftMouseReleased

    private void jButtonBottomRightMousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jButtonBottomRightMousePressed
      changeJButtonIcon(jButtonBottomRight);
      sendCommand(2);
    }//GEN-LAST:event_jButtonBottomRightMousePressed

    private void jButtonBottomRightMouseReleased(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jButtonBottomRightMouseReleased
     restoreJButtonIcon(jButtonBottomRight);
     stopThread();
    }//GEN-LAST:event_jButtonBottomRightMouseReleased

    private void jButtonSerialConnectActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonSerialConnectActionPerformed

        try {

            serialPortName=jComboBoxSerialPort.getSelectedItem().toString();
            portId = getPort(serialPortName);
            //portId = jComboBoxSerialPort.getSelectedItem().toString());
            if (port==null){
            port = (SerialPort) portId.open("iMac G3 DV display Properties", 10000);
            port.setSerialPortParams(
                    9600,
                    SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE);
            }//end if
        } catch (Exception e) {
            e.printStackTrace();
        } 

        jButtonSerialConnect.setEnabled(false);
        jButtonSerialDisconnect.setEnabled(true);
        jComboBoxSerialPort.setEnabled(false);

        
        
        

    }//GEN-LAST:event_jButtonSerialConnectActionPerformed

    private void jButtonSerialDisconnectActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonSerialDisconnectActionPerformed
        jButtonSerialConnect.setEnabled(true);
        jButtonSerialDisconnect.setEnabled(false);
        jComboBoxSerialPort.setEnabled(true);
        closePort();

     
    }//GEN-LAST:event_jButtonSerialDisconnectActionPerformed

    private void jButtonFactoryDefaultsActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButtonFactoryDefaultsActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_jButtonFactoryDefaultsActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
 


    
   
        /* Create and display the form */
//        java.awt.EventQueue.invokeLater(new Runnable() {
//            public void run() {
//                new Displays().setVisible(true);
//            }
//        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.ButtonGroup buttonGroupGeometry;
    private javax.swing.JButton jButtonBottomLeft;
    private javax.swing.JButton jButtonBottomRight;
    private javax.swing.JButton jButtonFactoryDefaults;
    private javax.swing.JButton jButtonRightBottom;
    private javax.swing.JButton jButtonRightTop;
    private javax.swing.JButton jButtonSerialConnect;
    private javax.swing.JButton jButtonSerialDisconnect;
    private javax.swing.JComboBox<String> jComboBoxSerialPort;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabelMonitorImage;
    private javax.swing.JPanel jPanelColor;
    private javax.swing.JPanel jPanelGeometry;
    private javax.swing.JPanel jPanelSerial;
    private javax.swing.JPanel jPanelSettings;
    private javax.swing.JRadioButton jRadioButtonHeightWidth;
    private javax.swing.JRadioButton jRadioButtonKeystone;
    private javax.swing.JRadioButton jRadioButtonParallelogram;
    private javax.swing.JRadioButton jRadioButtonPincushion;
    private javax.swing.JRadioButton jRadioButtonPosition;
    private javax.swing.JRadioButton jRadioButtonRotate;
    private javax.swing.JTabbedPane jTabbedPaneDisplay;
    // End of variables declaration//GEN-END:variables


void selectRadioButtons(){

        //set the ImageIcons
        jButtonRightTop.setEnabled(true);
        jButtonRightBottom.setEnabled(true);
        jButtonBottomLeft.setEnabled(true);
        jButtonBottomRight.setEnabled(true);

        if (buttonGroupGeometry.getSelection().equals(jRadioButtonPosition.getModel())) {
            jButtonRightTop.setIcon(positionImageMoveUp);
            jButtonRightBottom.setIcon(positionImageMoveDown);
            jButtonBottomLeft.setIcon(positionImageMoveLeft);
            jButtonBottomRight.setIcon(positionImageMoveRight);
        }

        if (buttonGroupGeometry.getSelection().equals(jRadioButtonHeightWidth.getModel())) {
            jButtonRightTop.setIcon(heightImageReduceHeight);
            jButtonRightBottom.setIcon(heightImageIncreaseHeight);
            jButtonBottomLeft.setIcon(WidthImageReduceWidth);
            jButtonBottomRight.setIcon(WidthImageIncreaseWidth);
        }

        if (buttonGroupGeometry.getSelection().equals(jRadioButtonPincushion.getModel())) {
            jButtonRightTop.setIcon(null);
            jButtonRightTop.setBorder(BorderFactory.createEmptyBorder());
            jButtonRightTop.setContentAreaFilled(false);
            jButtonRightBottom.setIcon(null);
            jButtonRightBottom.setBorder(BorderFactory.createEmptyBorder());
            jButtonRightBottom.setContentAreaFilled(false);
            jButtonBottomLeft.setIcon(pincushionImagePinch);
            jButtonBottomRight.setIcon(pincushionImageStretch);
            jButtonRightTop.setEnabled(false);
            jButtonRightBottom.setEnabled(false);

        }

        if (buttonGroupGeometry.getSelection().equals(jRadioButtonRotate.getModel())) {
            jButtonRightTop.setIcon(null);
            jButtonRightTop.setBorder(BorderFactory.createEmptyBorder());
            jButtonRightTop.setContentAreaFilled(false);
            jButtonRightBottom.setIcon(null);
            jButtonRightBottom.setBorder(BorderFactory.createEmptyBorder());
            jButtonRightBottom.setContentAreaFilled(false);
            jButtonBottomLeft.setIcon(rotateImageClockwise);
            jButtonBottomRight.setIcon(rotateImageCounterClockwise);
            jButtonRightTop.setEnabled(false);
        jButtonRightBottom.setEnabled(false);

    }

    if (buttonGroupGeometry.getSelection().equals(jRadioButtonKeystone.getModel())) {

        jButtonRightTop.setIcon(null);
        jButtonRightTop.setBorder(BorderFactory.createEmptyBorder());
        jButtonRightTop.setContentAreaFilled(false);
        jButtonRightBottom.setIcon(null);
        jButtonRightBottom.setBorder(BorderFactory.createEmptyBorder());
        jButtonRightBottom.setContentAreaFilled(false);
        jButtonBottomLeft.setIcon(keystoneImagePinchTop);
        jButtonBottomRight.setIcon(keystoneImageStretchTop);
        jButtonRightTop.setEnabled(false);
        jButtonRightBottom.setEnabled(false);

        }

        if (buttonGroupGeometry.getSelection().equals(jRadioButtonParallelogram.getModel())) {
            jButtonRightTop.setIcon(null);
            jButtonRightTop.setBorder(BorderFactory.createEmptyBorder());;
            jButtonRightTop.setContentAreaFilled(false);
            jButtonRightBottom.setIcon(null);
            jButtonRightBottom.setBorder(BorderFactory.createEmptyBorder());
            jButtonRightBottom.setContentAreaFilled(false);
            jButtonBottomLeft.setIcon(parallelogramImageTiltLeft);
            jButtonBottomRight.setIcon(parallelogramImageTiltRight);
            jButtonRightTop.setEnabled(false);
            jButtonRightBottom.setEnabled(false);

        }
    }//end selectRadioButtons

void changeJButtonIcon(JButton jb){
    
    tmpIcon=jb.getIcon();
    jb.setIcon(rectangleImage);

}//end method

void restoreJButtonIcon(JButton jb){

    jb.setIcon(tmpIcon);

}//end method

    void sendCommand(int command) {
        char cmd = '@';
        switch (command) {

            case 0:
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonPosition.getModel())) {
                    cmd = 'w';
                }
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonHeightWidth.getModel())) {
                    cmd = 'c';
                }


                break;

            case 1:
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonPosition.getModel())) {
                    cmd = 'z';
                }
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonHeightWidth.getModel())) {
                    cmd = 'r';
                }

                break;
            case 2:
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonPosition.getModel())) {
                    cmd = 's';
                }
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonHeightWidth.getModel())) {
                    cmd = 'f';
                }                
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonPincushion.getModel())) {
                    cmd = 'i';
                }
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonRotate.getModel())) {
                    cmd = 't';
                }
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonKeystone.getModel())) {
                    cmd = 'n';
                }
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonParallelogram.getModel())) {
                    cmd = 'v';
                }
                break;
            case 3:
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonPosition.getModel())) {
                    cmd = 'a';
                }
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonHeightWidth.getModel())) {
                    cmd = 'd';
                }                
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonPincushion.getModel())) {
                    cmd = 'u';
                }
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonRotate.getModel())) {
                    cmd = 'y';
                }
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonKeystone.getModel())) {
                    cmd = 'b';
                }
                if (buttonGroupGeometry.getSelection().equals(jRadioButtonParallelogram.getModel())) {
                    cmd = 'x';
                }
                break;


        }//end switch

        if (cmd != '@' && st==null && sendSerial==null) {
            
      
            st = new SerialTrigger();
            sendSerial = new Thread(st);
            st.setPort(port);
            st.setCharacter(cmd);
            sendSerial.start();
        }
    }//end method

    private void stopThread() {
        st.stopThread();
        sendSerial = null;
        st = null;

    }//end method

    /**
     * Searches for available ports
     *
     * @param port String the name of the port that you want to return
     * @return CommPortIdentifier
     */
    private CommPortIdentifier getPort(String port) {
        // Javacomm fields
        Enumeration portIdentifiers = CommPortIdentifier.getPortIdentifiers();
        CommPortIdentifier pid = null;
        while (portIdentifiers.hasMoreElements()) {
            pid = (CommPortIdentifier) portIdentifiers.nextElement();
            // this.portComboBox.addItem(pid.getName());
            if (pid.getName().equals(port)) {
                break;
            }
        }

        return pid;
    }// end getPort  
    
    public void closePort() {
        try {

            if (port != null) {
                port.close();
                //Thread.sleep(25);
                port = null;

            }//end if        

            if (portId != null) {
                portId = null;

            }//end if

        }//end try
        catch (Exception e) {
            e.printStackTrace();
        }//end catch
    }    
}//end class

//
//  singleSlideUIViewController.swift
//  tenda
//
//  Created by Anto on 31/03/16.
//  Copyright © 2016 Anto. All rights reserved.
//

import UIKit

class singleSlideUIViewController: UIViewController {
   
    @IBOutlet weak var closedSlidebar: UIView!
    
    @IBOutlet weak var automaticBtn: UIButton!
    @IBOutlet weak var manualBtn: UIButton!
    
    @IBOutlet weak var redBar: UIImageView!
    
    @IBOutlet weak var greenBar: UIImageView!

    @IBOutlet weak var automaticSlider: UISlider!
    @IBOutlet weak var AutomaticValue: UILabel!
    @IBOutlet weak var automaticGreen: UIView!
    
    
    
    var manual = false
    
    func activate(manual:boolean) {
        self.SlidebarBtn.alpha = (manual ? 100 : 0)
        self.SlidebarBtnSxRed.alpha = (manual ? 0 : 100)
        self.SlidebarBtnGrDx.alpha = (manual ? 100 : 0)
        self.SlidebarBtnDxRed.alpha = (manual ? 0 : 100)
    }

    @IBAction func onAutomaticBtn(sender: AnyObject) {
        UIView.animateWithDuration(0.3) {
            self.greenBar.alpha = 0
            self.redBar.alpha = 100
            
            self.automaticBtn.alpha = 0
            self.manualBtn.alpha = 100

            self.automaticGreen.alpha = 0
            
            manual = true
            
        }
        
    }
    @IBAction func onManualBtn(sender: AnyObject) {
        UIView.animateWithDuration(0.3) {
            self.greenBar.alpha = 100
            self.redBar.alpha = 0
            
            self.automaticBtn.alpha = 100
            self.manualBtn.alpha = 0

            self.automaticGreen.alpha = 100

            manual = false
        }
        
    }

    
    
    @IBAction func onSlidebarBtn(sender: AnyObject) {
        UIView.animateWithDuration(0.3, delay: 0, options: UIViewAnimationOptions.CurveEaseOut, animations: { 
            self.closedSlidebar.frame.origin.x = -262
            self.SlidebarBtn.alpha = 0
            self.SlidebarBtnGrDx.alpha = 100
            self.SlidebarBtnDxRed.alpha = 0
            }, completion: { activate(manual)
                }
                )
    }

    @IBAction func onSlidebarBtnDx(sender: AnyObject) {
        UIView.animateWithDuration(0.3, delay: 0, options: UIViewAnimationOptions.CurveEaseOut, animations: {
            self.closedSlidebar.frame.origin.x = 44
            self.SlidebarBtn.alpha = 100
            self.SlidebarBtnGrDx.alpha = 0
            }, completion: nil)
        
    }
    

    @IBAction func onSlidebarBtnDxRed(sender: AnyObject) {
        UIView.animateWithDuration(0.3, delay: 0, options: UIViewAnimationOptions.CurveEaseOut, animations: {
            self.closedSlidebar.frame.origin.x = 44
            self.SlidebarBtn.alpha = 100
            self.SlidebarBtnGrDx.alpha = 0
            }, completion: nil)
    }
    
    
    
}

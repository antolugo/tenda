//
//  singleSlideUIViewController.swift
//  tenda
//
//  Created by Anto on 31/03/16.
//  Copyright © 2016 Anto. All rights reserved.
//

import UIKit

class singleSlideUIViewController: UIViewController, UITextFieldDelegate {
    
    @IBOutlet weak var closedSlidebar: UIView!
    
    @IBOutlet weak var automaticBtn: UIButton!
    @IBOutlet weak var manualBtn: UIButton!
    
    @IBOutlet weak var redBar: UIImageView!
    
    @IBOutlet weak var greenBar: UIImageView!
    
    @IBOutlet weak var automaticSlider: UISlider!
    @IBOutlet weak var AutomaticValue: UILabel!
    @IBOutlet weak var automaticGreen: UIView!
    
    @IBOutlet weak var SxGr: UIButton!
    @IBOutlet weak var DxGr: UIButton!
    @IBOutlet weak var SxRed: UIButton!
    @IBOutlet weak var DxRed: UIButton!
    
    @IBOutlet weak var scrollView: UIScrollView!
    
    @IBOutlet weak var curtainName: UITextField!
    
    @IBOutlet weak var percRed: UILabel!
    @IBOutlet weak var percGr: UILabel!
    
    
    var manual = false
    var left = false
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Do any additional setup after loading the view, typically from a nib.
        
        self.curtainName.delegate = self;
        
        scrollView.contentSize = CGSizeMake(378, 768)
        
    }
    
    func textFieldShouldReturn(textField: UITextField) -> Bool {
        self.view.endEditing(true)
        return false
    }

    
    func activate(manual:Bool,left:Bool) {
        self.SxGr.alpha = !left ? (!manual ? 100 : 0) : 0
        self.SxRed.alpha = !left ? (!manual ? 0 : 100) : 0
        self.DxGr.alpha = left ? (!manual ? 100 : 0) : 0
        self.DxRed.alpha = left ? (!manual ? 0 : 100) : 0
    }
    
    @IBAction func onAutomaticBtn(sender: AnyObject) {
        UIView.animateWithDuration(0.3) {
            self.greenBar.alpha = 0
            self.redBar.alpha = 100
            
            self.automaticBtn.alpha = 0
            self.manualBtn.alpha = 100
            
            self.automaticGreen.alpha = 0
            
            self.percGr.alpha = 0
            self.percRed.alpha = 100
            
            self.manual = true
            self.activate(self.manual,left: self.left)
            
            
        }
        
    }
    @IBAction func onManualBtn(sender: AnyObject) {
        UIView.animateWithDuration(0.3) {
            self.greenBar.alpha = 100
            self.redBar.alpha = 0
            
            self.automaticBtn.alpha = 100
            self.manualBtn.alpha = 0
            
            self.automaticGreen.alpha = 100
            
            self.percGr.alpha = 100
            self.percRed.alpha = 0
            
            self.manual = false
            self.activate(self.manual,left: self.left)
        
       }
    }
    
    
    
    @IBAction func onSlidebarBtn(sender: AnyObject) {
        UIView.animateWithDuration(0.3, delay: 0, options: UIViewAnimationOptions.CurveEaseOut, animations: {
            self.closedSlidebar.frame.origin.x = -254
            self.left = true
            self.activate(self.manual,left: self.left)
            }, completion:nil
        )
    }
    
    @IBAction func onSlidebarBtnSxRed(sender: AnyObject) {
        UIView.animateWithDuration(0.3, delay: 0, options: UIViewAnimationOptions.CurveEaseOut, animations: {
            self.closedSlidebar.frame.origin.x = -254
            self.left = true
            self.activate(self.manual,left: self.left)
            }, completion:nil)
    }
    
    @IBAction func onSlidebarBtnDx(sender: AnyObject) {
        UIView.animateWithDuration(0.3, delay: 0, options: UIViewAnimationOptions.CurveEaseOut, animations: {
            self.closedSlidebar.frame.origin.x = 44
            self.left = false
            self.activate(self.manual,left: self.left)
            }, completion: nil)
        
    }
    
    
    @IBAction func onSlidebarBtnDxRed(sender: AnyObject) {
        UIView.animateWithDuration(0.3, delay: 0, options: UIViewAnimationOptions.CurveEaseOut, animations: {
            self.closedSlidebar.frame.origin.x = 44
            self.left = false
            self.activate(self.manual,left: self.left)
            }, completion: nil)
    }
    


    
    
}


//
//  ViewController.swift
//  parking
//
//  Created by epl on 2016/6/6.
//  Copyright © 2016年 epl. All rights reserved.
//

import UIKit
import Parse

class ViewController: UIViewController {
    
    @IBOutlet weak var itemchange1: UIButton!
    @IBOutlet weak var itemchange2: UIButton!
    @IBOutlet weak var itemchange3: UIButton!
    @IBOutlet weak var itemchange6: UIButton!
    @IBOutlet weak var itemchange5: UIButton!
    @IBOutlet weak var itemchange4: UIButton!
    
    @IBOutlet weak var waitingnum4: UILabel!
    @IBOutlet weak var waitingnum1: UILabel!
    @IBOutlet weak var waitingnum5: UILabel!
    @IBOutlet weak var waitingnum6: UILabel!
    @IBOutlet weak var waitingnum3: UILabel!
    @IBOutlet weak var waitingnum2: UILabel!
    
    
    @IBAction func item1(sender: AnyObject) {
   
        let query1 = PFQuery(className:"parkingSpace")
        query1.getObjectInBackgroundWithId("KjFWpM1LaQ"){
            (preobject: PFObject?, error: NSError?) -> Void in
            
            if error == nil || preobject != nil {
                print("preobject=",preobject)
                
                var waitingNum=preobject?.objectForKey("waitingNum") as! NSNumber
                waitingNum = waitingNum.unsignedIntegerValue + 1
                preobject!["waitingNum"] = waitingNum
                
                self.checkbutton(1,empty: true,waitingNum: waitingNum)
                preobject!.saveInBackgroundWithBlock { (success: Bool, error: NSError?) -> Void in
                    print("Object has been saved.")
                }
            }
        }
        
      }
    
    @IBAction func item2(sender: AnyObject) {
        
        let query1 = PFQuery(className:"parkingSpace")
        query1.getObjectInBackgroundWithId("F58MnDPown"){
            (preobject: PFObject?, error: NSError?) -> Void in
            
            if error == nil || preobject != nil {
                print("preobject=",preobject)
                
                var waitingNum=preobject?.objectForKey("waitingNum") as! NSNumber
                waitingNum = waitingNum.unsignedIntegerValue + 1
                preobject!["waitingNum"] = waitingNum
                preobject!.saveInBackgroundWithBlock { (success: Bool, error: NSError?) -> Void in
                    print("Object has been saved.")
                }
            }
        }
    }

    @IBAction func searchButton(sender: AnyObject) {
       
        let query = PFQuery(className:"parkingSpace")
                query.findObjectsInBackgroundWithBlock { (objects: [PFObject]?, error: NSError?) -> Void in
            if error == nil {
                print("Successfully retrieved \(objects!.count) datas.")
                if let objects = objects {
                    for object in objects {
                        
                        let item = object.objectForKey("itemNum") as! NSNumber
                        let empty = object.objectForKey("empty") as! Bool
                        let waitingNum = object.objectForKey("waitingNum") as! NSNumber
                        
                        
                        print("item=",item)
                        print("empty=",empty)
                        self.checkbutton(item,empty: empty,waitingNum: waitingNum)
                        
                    }
                }
            }
        }
        
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
   
    func checkbutton(item: NSNumber,empty:Bool,waitingNum:NSNumber)
    {
        
        if(item == 1 && empty == false)
        {
            
            self.itemchange1.backgroundColor = UIColor.darkGrayColor()
            self.itemchange1.enabled = false
            self.waitingnum1.text="0"
        }
        else if(item == 1 && empty == true)
        {
            self.itemchange1.backgroundColor = UIColor.init(red: 0.1725, green: 0.5216, blue: 0.9176, alpha: 1.0);
            self.itemchange1.enabled = true
            self.waitingnum1.text = String(waitingNum)
        }
        
        
        if(item == 2 && empty == false)
        {
            self.itemchange2.backgroundColor = UIColor.darkGrayColor()
            self.itemchange2.enabled = false
            self.waitingnum2.text="0"
        }
        else if(item == 2 && empty == true)
        {
            self.itemchange2.backgroundColor = UIColor.init(red: 0.1725, green: 0.5216, blue: 0.9176, alpha: 1.0);
            self.itemchange2.enabled = true
            self.waitingnum2.text = String(waitingNum)
            
        }
        
        if(item == 3 && empty == false)
        {
            self.itemchange3.backgroundColor = UIColor.darkGrayColor()
            self.itemchange3.enabled = false
            self.waitingnum3.text="0"
        }
        else if(item == 3 && empty == true)
        {
            self.itemchange3.backgroundColor = UIColor.init(red: 0.1725, green: 0.5216, blue: 0.9176, alpha: 1.0);
            self.itemchange3.enabled = true
            self.waitingnum3.text = String(waitingNum)
        }
        
        if(item == 4 && empty == false)
        {
            self.itemchange4.backgroundColor = UIColor.darkGrayColor()
            self.itemchange4.enabled = false
            self.waitingnum4.text="0"
        }
        else if(item == 4 && empty == true)
        {
            self.itemchange4.backgroundColor = UIColor.init(red: 0.1725, green: 0.5216, blue: 0.9176, alpha: 1.0);
            self.itemchange4.enabled = true
            self.waitingnum4.text = String(waitingNum)
        }
        
        if(item == 5 && empty == false)
        {
            self.itemchange5.backgroundColor = UIColor.darkGrayColor()
            self.itemchange5.enabled = false
            self.waitingnum5.text="0"
        }
        else if(item == 5 && empty == true)
        {
            self.itemchange5.backgroundColor = UIColor.init(red: 0.1725, green: 0.5216, blue: 0.9176, alpha: 1.0);
            self.itemchange5.enabled = true
            self.waitingnum5.text = String(waitingNum)

        }
        
        if(item == 6 && empty == false)
        {
            self.itemchange6.backgroundColor = UIColor.darkGrayColor()
            self.itemchange6.enabled = false
            self.waitingnum6.text="0"
        }
        else if(item == 6 && empty == true)
        {
            self.itemchange6.backgroundColor = UIColor.init(red: 0.1725, green: 0.5216, blue: 0.9176, alpha: 1.0);
            self.itemchange6.enabled = true
            self.waitingnum6.text = String(waitingNum)

        }
    }

}


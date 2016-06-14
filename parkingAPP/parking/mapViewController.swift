//
//  map.swift
//  parking
//
//  Created by epl on 2016/6/8.
//  Copyright © 2016年 epl. All rights reserved.
//

import MapKit
import UIKit
import CoreLocation
import Parse



class mapViewController: UIViewController,MKMapViewDelegate,CLLocationManagerDelegate{
    
    var PFobjects:[PFObject] = []
    var flagremove:Bool = true
    var firstLocation:Bool = true
    @IBOutlet weak var text: UILabel!
    @IBOutlet weak var mapView: MKMapView!
    var myLocationManager : CLLocationManager! //座標管理元件
  
    @IBAction func backButton(sender: AnyObject) {
        text.text = "pig"

    }
    override func viewDidLoad() {
        super.viewDidLoad()
        myLocationManager = CLLocationManager()
        myLocationManager.delegate = self
        myLocationManager.distanceFilter = kCLLocationAccuracyNearestTenMeters
        myLocationManager.desiredAccuracy = kCLLocationAccuracyBest
        myLocationManager.requestAlwaysAuthorization()
        myLocationManager.startUpdatingLocation()
        mapView.delegate = self
        mapView.showsUserLocation = true
    }
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(true)
        PFobjects = []
        parsedata()
    }
    override func viewDidDisappear(animated: Bool) {
        myLocationManager.stopUpdatingLocation();
    }
 // MARK: self Methods
    func position(){
        
        let allAnnotations = mapView.annotations
        mapView.removeAnnotations(allAnnotations)
        mapView.showsUserLocation = true

        for object in PFobjects
        {
            let anno = MKPointAnnotation()
            let waitNum = object.objectForKey("waitingNum") as! NSNumber
            let empty = object.objectForKey("empty") as! Bool
            let coordinate = object.objectForKey("coordinate") as! NSString
            let waitingNumString = String(format:"Waiting number :%@" ,waitNum)
            anno.title = object.objectForKey("physicalAddress") as? String
            if empty == true {
            anno.subtitle = waitingNumString
            }else {
            anno.subtitle = "Parking was stopped"
            }
            let coordinateArray =  coordinate.componentsSeparatedByString(",")
           anno.coordinate = CLLocationCoordinate2DMake(Double(coordinateArray[0])!,Double(coordinateArray[1])!)
            
             mapView.addAnnotation(anno)
            
        }
    }
    
    func parsedata()
    {
        let query = PFQuery(className:"parkingSpace")
        query.findObjectsInBackgroundWithBlock { (objects: [PFObject]?, error: NSError?) -> Void in
            if error == nil {
                print("Successfully retrieved \(objects!.count) datas.")
                if let objects = objects {
                    
                    for object in objects {
                        
                        self.PFobjects.append(object)
                        
                    }
                    self.position()
                }
            }
        }
        
    }
// MARK : - CLLocationManagerDelegate
    func locationManager(manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        let currentLocation = locations.last
        if firstLocation == true {
            var region = mapView.region
            region.center = (currentLocation?.coordinate)!
            region.span = MKCoordinateSpan(latitudeDelta: 0.01, longitudeDelta: 0.01)
            mapView.setRegion(region, animated: true)
            firstLocation = false
        }
    }
// MARK : - MKMapViewDelegate
    func mapView(mapView: MKMapView, didSelectAnnotationView view: MKAnnotationView) {
        if (view.annotation?.title)! != "Current Location" {
        let alertcontrol = UIAlertController(title: "Would you need to go here ", message: "Choose a better space for parking", preferredStyle: .Alert )
        let alertrok = UIAlertAction(title: "OK", style: .Default ) { (UIAlertAction) in
           
            let directpage = self.storyboard?.instantiateViewControllerWithIdentifier("Direction") as! DirectionViewController
            directpage.target = view.annotation as! MKPointAnnotation
               for PFobject in self.PFobjects {
                if (view.annotation?.title)! == PFobject.objectForKey("physicalAddress") as? String {
                  directpage.object = PFobject
              }
            }
            self.dismissViewControllerAnimated(true, completion: nil)
            self.presentViewController(directpage, animated: true, completion: nil)
            let query1 = PFQuery(className:"parkingSpace")
            for object in self.PFobjects
            {
                if((view.annotation?.title!!)! == object.objectForKey("physicalAddress") as? String)
                {
                    query1.getObjectInBackgroundWithId(object.objectId!, block: { (preobject:PFObject?, error: NSError?) -> Void in
                        
                        if error == nil || preobject != nil {
                            var waitingNum=preobject?.objectForKey("waitingNum") as! NSNumber
                            waitingNum = waitingNum.unsignedIntegerValue + 1
                            preobject!["waitingNum"] = waitingNum
                            
                            preobject!.saveInBackgroundWithBlock { (success: Bool, error: NSError?) -> Void in
                                print("Object has been saved.")
                            }
                        }
                        
                    })
                    return
                }
            }
        }
        let alertcancel = UIAlertAction(title: "Cancel", style: .Cancel, handler: nil)
        alertcontrol.addAction(alertrok)
        alertcontrol.addAction(alertcancel)
        if (view.annotation?.subtitle)! != "Parking was stopped" {
        self.presentViewController(alertcontrol, animated: true, completion: nil)
        }
      }
    }
    
     func mapView(mapView: MKMapView, viewForAnnotation annotation: MKAnnotation) -> MKAnnotationView? {
        
        if(annotation.isEqual(mapView.userLocation))
        {
            return nil
        }
         let pointView = MKPinAnnotationView()
    
        
        let annoArray:NSArray = annotation.subtitle!!.componentsSeparatedByString(":")
        let subTitle = annoArray.lastObject as! NSString
        if (subTitle.isEqualToString("Parking was stopped")) {
            pointView.pinTintColor = UIColor.redColor()
        }else {
            pointView.pinTintColor = UIColor.greenColor()
        }
        pointView.canShowCallout = true
        return pointView;
    }

    
    
}
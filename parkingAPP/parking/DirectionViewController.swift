//
//  DirectionViewController.swift
//  parking
//
//  Created by epl on 2016/6/10.
//  Copyright © 2016年 epl. All rights reserved.
//

import UIKit
import CoreLocation
import MapKit
import Parse

class DirectionViewController: UIViewController, CLLocationManagerDelegate,MKMapViewDelegate{
    var target : MKPointAnnotation = MKPointAnnotation()
    var object : PFObject! = nil
    var firstLocation = true
    @IBAction func StopButton(sender: AnyObject) {
    let alertcontrol = UIAlertController(title: "Would you need to stop navigation?",
                                         message: "Choose a better space for parking", preferredStyle: .Alert )
    let alertrok = UIAlertAction(title: "OK", style: .Default ) { (UIAlertAction) in
        let query1 = PFQuery(className:"parkingSpace")
        query1.getObjectInBackgroundWithId(self.object.objectId!,
                                           block: { (preobject:PFObject?, error: NSError?) -> Void in
        if error == nil || preobject != nil {
            var waitingNum=preobject?.objectForKey("waitingNum") as! NSNumber
            waitingNum = waitingNum.unsignedIntegerValue - 1
            preobject!["waitingNum"] = waitingNum
            preobject!.saveInBackgroundWithBlock { (success: Bool, error: NSError?) -> Void in
                            print("Object has been saved.")
                }
                  self.dismissViewControllerAnimated(true, completion: nil)
                }
            })
       }
        
        let alertcancel = UIAlertAction(title: "Cancel", style: .Cancel, handler: nil)
        
        alertcontrol.addAction(alertrok)
        alertcontrol.addAction(alertcancel)
        
        self.presentViewController(alertcontrol, animated: true, completion: nil)
    }
    @IBOutlet weak var DmapView: MKMapView!
   
    var myLocationManager : CLLocationManager! //座標管理元件
    
    override func viewDidLoad() {
        super.viewDidLoad()
        myLocationManager = CLLocationManager()
        myLocationManager.delegate = self
        myLocationManager.distanceFilter =
        kCLLocationAccuracyNearestTenMeters
        myLocationManager.desiredAccuracy =
        kCLLocationAccuracyBest
        myLocationManager.requestAlwaysAuthorization()
        myLocationManager.startUpdatingLocation()
        DmapView.showsUserLocation = true
        DmapView.addAnnotation(target)
        DmapView.delegate = self
        getdirections()
    }

    func locationManager(manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        let currentLocation = locations.last
        if firstLocation == true {
        var region = DmapView.region
        region.center = (currentLocation?.coordinate)!
        region.span = MKCoordinateSpan(latitudeDelta: 0.01, longitudeDelta: 0.01)
        DmapView.setRegion(region, animated: true)
        firstLocation = false
        }
    }

    func getdirections()
    {
        let request:MKDirectionsRequest = MKDirectionsRequest()
        request.source = MKMapItem.mapItemForCurrentLocation()
        let placemark = MKPlacemark(coordinate: target.coordinate, addressDictionary: nil)
        request.destination = MKMapItem(placemark: placemark)
        request.requestsAlternateRoutes = false
        request.transportType = .Automobile
        let directions = MKDirections(request: request)
        directions.calculateDirectionsWithCompletionHandler { response, error in
            if error != nil
            {
                print("i am error")
            }else{
                for route in response!.routes {
            self.DmapView.addOverlay(route.polyline, level: .AboveRoads)
                }
            }
        }
    }
    func mapView(mapView: MKMapView, rendererForOverlay overlay: MKOverlay) -> MKOverlayRenderer {
        let render = MKPolylineRenderer(overlay: overlay)
        render.strokeColor = UIColor.redColor()
        render.lineWidth = 5.0
        return render
    }
  
}

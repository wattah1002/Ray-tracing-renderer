class sphere: public hitable {
    public: sphere() {}
    sphere(vec3 cen, float r, material *m): center(cen),
    radius(r),
    mat_ptr(m) {};
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    vec3 center;
    float radius;
    material * mat_ptr;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b*b -4.0 * a * c;

    if (discriminant > 0){
        float temp_t = (-b -sqrt(discriminant)) / (2.0 * a);
        if (temp_t < t_max && temp_t > t_min) {
            rec.t = temp_t;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp_t = (-b + sqrt(discriminant)) / (2.0 * a);
        if (temp_t < t_max && temp_t > t_min){
            rec.t = temp_t;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}
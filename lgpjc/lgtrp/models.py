import datetime
from django.db import models
from django.utils import timezone

class Student(models.Model):
    name = models.CharField(max_length=256, null=False, unique=True)
    registration_date = models.DateTimeField('Registration Date', default=timezone.now)
    GENDERS = (
        ('M', 'Male'),
        ('F', 'Female'),
    )
    gender = models.CharField(max_length=1, choices=GENDERS, null=False)

    def __str__(self):
        return self.name

    def was_registered_recently(self):
        now = timezone.now()
        return now - datetime.timedelta(days=30) <= self.registration_date <= now
        
    def get_absolute_url(self):
        return u'/lgtrp/student/edit/%d' % self.id 
    
class School(models.Model):
    name = models.CharField(max_length=256, unique=True, null=False)
    students = models.ManyToManyField(Student)
    registration_date = models.DateTimeField('Registration Date', default=timezone.now, null=False)
    
    def __str__(self):
        return self.name
        
    def get_absolute_url(self):	
        return u'/lgtrp/school/edit/%d' % self.id 
        
    def was_registered_recently(self):
        now = timezone.now()
        return now - datetime.timedelta(days=30) <= self.registration_date <= now


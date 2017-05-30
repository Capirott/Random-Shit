import datetime
from django.db import models
from django.utils import timezone

class Student(models.Model):
    name = models.CharField(max_length=256)
    registration_date = models.DateTimeField('Student Registration Date')
    GENDERS = (
        ('M', 'Male'),
        ('F', 'Female'),
    )
    gender = models.CharField(max_length=1, choices=GENDERS)

    def __str__(self):
        return self.name

    def was_registered_recently(self):
        now = timezone.now()
        return now - datetime.timedelta(days=30) <= self.registration_date <= now
    
class School(models.Model):
    name = models.CharField(max_length=256)
    students = models.ManyToManyField(Student)
    
    def __str__(self):
        return self.name

